#include "protocol.h"
#include "frame.h"
#include "flash_backup.h"
#include "fpga_dump.h"
#include "screenshot.h"
#include "serial.h"
#include "zw_api.h"

#define CONTAINER_ZWSHOT 1u
#define CONTAINER_ZWDUMP 2u
#define CONTAINER_ZWFLSH 3u
#define PROTOCOL_CAPS 0x8Fu /* bits 0-3 and 7: base protocol + flash reads */
#define PROTOCOL_ACK_MIN_MS    500u
#define PROTOCOL_ACK_MARGIN_MS 100u
#define PROTOCOL_RETRIES       3u
#define PROTOCOL_BAUD_WINDOW_MS 1000u
#define PROTOCOL_DUMP_WAIT_MS  2000u
#define PROTOCOL_RX_GAP_MS     100u

typedef struct {
    uint8_t begin_type;
    uint8_t container;
    void (*prepare)(void);
    uint32_t (*total)(void);
    void (*start)(void);
    void (*read)(uint8_t *dst, uint32_t len);
} container_ops;

static const container_ops shot_ops = {
    FRAME_SHOT_BEGIN, CONTAINER_ZWSHOT,
    screenshot_prepare, screenshot_total, screenshot_start, screenshot_read
};

static const container_ops dump_ops = {
    FRAME_DUMP_BEGIN, CONTAINER_ZWDUMP,
    fpga_dump_prepare, fpga_dump_total, fpga_dump_start, fpga_dump_read
};

static const container_ops persist_ops = {
    FRAME_PERSIST_BEGIN, CONTAINER_ZWFLSH,
    flash_backup_prepare, flash_backup_total, flash_backup_start,
    flash_backup_read
};

typedef enum {
    ACK_NONE = 0,
    ACK_ADVANCE,
    ACK_RETRY,
    ACK_ABORTED,
    ACK_TIMEOUT
} ack_result;

typedef struct {
    uint16_t xid;
    uint16_t expected;
    uint16_t abort_seq;
    uint8_t begin;
    ack_result result;
} ack_ctx;

static uint8_t uart_masked;
static uint8_t dump_pending;
static uint16_t dump_xid;
static uint32_t dump_deadline;
static uint8_t transfer_active;
static uint16_t transfer_xid;
static uint8_t rx_valid_seen;
static uint32_t rx_last_tick;
static ack_ctx *current_ack;
static uint8_t data_buf[FRAME_MAX_DATA];

static void protocol_parse(frame_handler handler);
static void handle_request(const frame_view *f);

static void put_le16(uint8_t *p, uint16_t v) {
    p[0] = (uint8_t)(v & 0xFFu);
    p[1] = (uint8_t)(v >> 8);
}

static void put_le32(uint8_t *p, uint32_t v) {
    p[0] = (uint8_t)(v & 0xFFu);
    p[1] = (uint8_t)((v >> 8) & 0xFFu);
    p[2] = (uint8_t)((v >> 16) & 0xFFu);
    p[3] = (uint8_t)((v >> 24) & 0xFFu);
}

static uint16_t get_le16(const uint8_t *p) {
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t get_le32(const uint8_t *p) {
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static void send_error(uint8_t code, uint8_t request_type, uint16_t seq, uint16_t detail) {
    uint8_t payload[4];

    payload[0] = code;
    payload[1] = request_type;
    put_le16(payload + 2, detail);
    frame_send(FRAME_ERROR, seq, payload, 4u);
}

static void send_info(uint16_t seq) {
    uint8_t payload[9];

    payload[0] = FRAME_VERSION;
    put_le16(payload + 1, FRAME_MAX_CONTROL);
    put_le16(payload + 3, FRAME_MAX_DATA);
    put_le32(payload + 5, PROTOCOL_CAPS);
    frame_send(FRAME_INFO, seq, payload, 9u);
}

static void send_baud_status(uint16_t seq, uint8_t status) {
    frame_send(FRAME_BAUD_STATUS, seq, &status, 1u);
}

static void send_begin(uint8_t type, uint16_t xid, uint8_t container, uint32_t total) {
    uint8_t payload[10];

    payload[0] = FRAME_OK;
    put_le16(payload + 1, xid);
    payload[3] = container;
    put_le16(payload + 4, FRAME_MAX_DATA);
    put_le32(payload + 6, total);
    frame_send(type, xid, payload, 10u);
}


static uint32_t ack_timeout_ms(void) {
    uint32_t baud = serial_baud();
    uint32_t frame_ms = ((uint32_t)(FRAME_MAX_DATA + 12u) * 10u * 1000u) /
                        baud;
    uint32_t timeout = 2u * frame_ms + PROTOCOL_ACK_MARGIN_MS;

    return (timeout < PROTOCOL_ACK_MIN_MS) ? PROTOCOL_ACK_MIN_MS : timeout;
}

static void protocol_parse(frame_handler handler) {
    frame_view view;

    while (serial_rx_count() != 0u) {
        uint8_t b = serial_getc();

        rx_last_tick = HAL_GetTick();
        switch (frame_parser_feed(b, &view)) {
        case FRAME_PARSE_FRAME:
            rx_valid_seen = 1u;
            handler(&view);
            break;
        case FRAME_PARSE_BAD_VERSION:
            rx_valid_seen = 1u;
            send_error(FRAME_BAD_VERSION, view.type, view.seq, view.seq);
            break;
        case FRAME_PARSE_BAD_LENGTH:
            rx_valid_seen = 1u;
            send_error(FRAME_BAD_LENGTH, view.type, view.seq, view.seq);
            break;
        default:
            break;
        }
    }

    if (frame_parser_busy() != 0u &&
        (uint32_t)(HAL_GetTick() - rx_last_tick) >= PROTOCOL_RX_GAP_MS)
        frame_parser_reset();
}

static ack_result transfer_wait(ack_ctx *ctx);

static void ack_frame(const frame_view *f) {
    ack_ctx *ctx = current_ack;

    if (ctx == 0)
        return;

    if (f->type == FRAME_DATA_ACK) {
        uint16_t xid;
        uint16_t next;

        if (f->len != 5u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            return;
        }
        xid = get_le16(f->payload);
        next = get_le16(f->payload + 2);
        if (xid != ctx->xid)
            return;

        if (ctx->begin != 0u) {
            if (f->payload[4] == FRAME_OK && next == 0u)
                ctx->result = ACK_ADVANCE;
            else if (f->payload[4] == FRAME_CRC_ERROR ||
                     f->payload[4] == FRAME_OUT_OF_ORDER)
                ctx->result = ACK_RETRY;
            return;
        }

        if (f->payload[4] == FRAME_OK) {
            if (next == (uint16_t)(ctx->expected + 1u))
                ctx->result = ACK_ADVANCE;
            else if (next <= ctx->expected)
                ctx->result = ACK_RETRY;
        } else if (f->payload[4] == FRAME_CRC_ERROR ||
                   f->payload[4] == FRAME_OUT_OF_ORDER) {
            ctx->result = ACK_RETRY;
        }
        return;
    }

    if (f->type == FRAME_ABORT) {
        uint16_t xid;

        if (f->len != 2u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            return;
        }
        xid = get_le16(f->payload);
        if (xid == 0u || xid == ctx->xid) {
            ctx->abort_seq = f->seq;
            ctx->result = ACK_ABORTED;
        }
        return;
    }

    send_error(FRAME_BUSY, f->type, f->seq, ctx->xid);
}

static ack_result transfer_wait(ack_ctx *ctx) {
    uint32_t timeout = ack_timeout_ms();
    uint32_t start = HAL_GetTick();

    current_ack = ctx;
    ctx->result = ACK_NONE;
    for (;;) {
        protocol_parse(ack_frame);
        if (ctx->result != ACK_NONE)
            break;
        if ((uint32_t)(HAL_GetTick() - start) >= timeout) {
            ctx->result = ACK_TIMEOUT;
            break;
        }
        serial_wdt_feed();
        HAL_Delay(1u);
    }
    current_ack = 0;
    return ctx->result;
}

static void run_transfer(const container_ops *ops, uint16_t xid, uint8_t request_type) {
    ack_ctx ctx;
    uint32_t total;
    uint32_t offset;
    uint16_t seq;
    uint32_t tries;

    transfer_active = 1u;
    transfer_xid = xid;

    ops->prepare();
    total = ops->total();

    ctx.xid = xid;
    ctx.abort_seq = xid;
    ctx.result = ACK_NONE;

    for (tries = 0u; ; tries++) {
        send_begin(ops->begin_type, xid, ops->container, total);
        ctx.begin = 1u;
        ctx.expected = 0u;
        if (transfer_wait(&ctx) == ACK_ADVANCE)
            break;
        if (ctx.result == ACK_ABORTED) {
            send_error(FRAME_ABORTED, FRAME_ABORT, ctx.abort_seq, xid);
            goto done;
        }
        if (tries >= PROTOCOL_RETRIES) {
            send_error(FRAME_TIMEOUT, request_type, xid, xid);
            goto done;
        }
    }

    ops->start();
    offset = 0u;
    seq = 0u;
    tries = 0u;
    for (;;) {
        uint32_t len = total - offset;

        if (len > FRAME_MAX_DATA)
            len = FRAME_MAX_DATA;
        if (tries == 0u)
            ops->read(data_buf, len);
        frame_send(FRAME_DATA, seq, data_buf, (uint16_t)len);

        ctx.begin = 0u;
        ctx.expected = seq;
        if (transfer_wait(&ctx) == ACK_ADVANCE) {
            offset += len;
            seq++;
            if (offset >= total)
                break;
            tries = 0u;
            continue;
        }
        if (ctx.result == ACK_ABORTED) {
            send_error(FRAME_ABORTED, FRAME_ABORT, ctx.abort_seq, xid);
            goto done;
        }
        if (tries >= PROTOCOL_RETRIES) {
            send_error(FRAME_TIMEOUT, request_type, xid, xid);
            goto done;
        }
        tries++;
    }

done:
    transfer_active = 0u;
}

static void set_baud(uint16_t seq, uint32_t rate) {
    uint32_t old = serial_baud();
    uint32_t start;

    if (rate == 0u || serial_baud_valid(rate) == 0u) {
        send_baud_status(seq, FRAME_BAD_RATE);
        return;
    }
    send_baud_status(seq, FRAME_OK);
    if (rate == old)
        return;

    serial_drain();
    frame_parser_reset();
    serial_set_baud(rate);

    rx_valid_seen = 0u;
    start = HAL_GetTick();
    while (rx_valid_seen == 0u) {
        protocol_parse(handle_request);
        if (rx_valid_seen != 0u)
            return;
        if ((uint32_t)(HAL_GetTick() - start) >= PROTOCOL_BAUD_WINDOW_MS)
            break;
        serial_wdt_feed();
        HAL_Delay(1u);
    }

    serial_drain();
    frame_parser_reset();
    serial_set_baud(old);
}

static void abort_idle(uint16_t xid, const frame_view *f) {
    if (dump_pending != 0u && (xid == 0u || xid == dump_xid)) {
        dump_pending = 0u;
        send_error(FRAME_ABORTED, FRAME_ABORT, f->seq, dump_xid);
    }
}

static void handle_request(const frame_view *f) {

    if (f->type == FRAME_ABORT) {
        if (f->len != 2u)
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
        else
            abort_idle(get_le16(f->payload), f);
        return;
    }

    if (f->type == FRAME_DATA_ACK) {
        if (f->len != 5u)
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
        return;
    }


    switch (f->type) {
    case FRAME_HELLO:
        if (f->len != 0u)
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
        else
            send_info(f->seq);
        break;

    case FRAME_SET_BAUD:
        if (f->len != 4u)
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
        else
            set_baud(f->seq, get_le32(f->payload));
        break;
    case FRAME_SCREENSHOT:
        if (f->len != 0u || f->seq == 0u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            break;
        }
        run_transfer(&shot_ops, f->seq, FRAME_SCREENSHOT);
        break;

    case FRAME_DUMP:
        if (f->len != 0u || f->seq == 0u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            break;
        }
        if (fpga_dump_busy() != 0u) {
            dump_pending = 1u;
            dump_xid = f->seq;
            dump_deadline = HAL_GetTick() + PROTOCOL_DUMP_WAIT_MS;
        } else {
            run_transfer(&dump_ops, f->seq, FRAME_DUMP);
        }
        break;

    case FRAME_PERSIST:
        if (f->len != FRAME_PERSIST_REQ_LEN || f->seq == 0u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            break;
        }
        if (flash_backup_range(get_le32(f->payload), get_le32(f->payload + 4u)) == 0u) {
            send_error(FRAME_BAD_PARAM, f->type, f->seq, f->seq);
            break;
        }
        run_transfer(&persist_ops, f->seq, FRAME_PERSIST);
        break;



    default:
        send_error(FRAME_UNKNOWN_TYPE, f->type, f->seq, f->seq);
        break;
    }
}

static void dump_poll(void) {
    if (dump_pending == 0u)
        return;
    if (fpga_dump_busy() != 0u &&
        (int32_t)(dump_deadline - HAL_GetTick()) > 0)
        return;
    dump_pending = 0u;
    run_transfer(&dump_ops, dump_xid, FRAME_DUMP);
}

void protocol_poll(void) {
    if (uart_masked == 0u) {
        serial_mask_irqs();
        uart_masked = 1u;
    }

    protocol_parse(handle_request);
    dump_poll();
}
