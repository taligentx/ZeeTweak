#include "fpga_dump.h"
#include "container.h"
#include "dump_codec.h"
#include "frame.h"
#include "serial.h"
#include "zw_api.h"

#define DUMP_VERSION     5u
#define DUMP_HEADER_LEN  128u
#define DUMP_FLAG_CH2    0x00000001u
#define DUMP_FLAG_BUSY   0x00000002u
#define DUMP_FLAG_FULL   0x00000004u
#define DUMP_PAD         0x1Au
#define DUMP_CHUNK       3000u
#define DUMP_SAMPLES_MAX 60000u
#define DUMP_DIVISIONS   12u
#define GS_CH2_ENABLED      0x02u
#define GS_RECORD_LEN       0x04u
#define GS_RING_LEN         0x0Cu
#define GS_TIMEBASE_NS_L    0x14u
#define GS_TIMEBASE_NS_H    0x18u
#define GS_WIN_ADDR_MS      0x30u
#define GS_CURSOR           0x3Cu
#define GS_SAMPLE_RATE_L    0xC0u
#define GS_PRE_DEPTH        0xC8u
#define GS_SCAN_MODE        0xDCu
#define GS_ROLL_ENABLE      0xDDu
#define DUMP_SETTINGS_LEN  0x154u
#define DUMP_MEAS_LEN      100u
#define DUMP_STATE_LEN     (DUMP_SETTINGS_LEN + 2u * DUMP_MEAS_LEN)
#define DUMP_SETTINGS ((const volatile uint8_t *)global_settings)

static uint8_t dump_state[DUMP_STATE_LEN];
static uint8_t dump_header[DUMP_HEADER_LEN];
static uint32_t dump_samples;
static uint32_t dump_ch2;
static uint32_t dump_window_len;
static int32_t  dump_window_start;
static uint32_t dump_trigger;
static uint32_t dump_record_start;
static uint32_t dump_fetch_delta;
static uint32_t dump_ring;
static uint32_t dump_encoding;
static uint32_t dump_encoded_len;
static uint32_t dump_total_bytes;
static uint32_t dump_offset;
static dump_codec_plan dump_plan[2];

static uint32_t settings_u32(uint32_t off) {
    return (uint32_t)dump_state[off] |
           ((uint32_t)dump_state[off + 1u] << 8) |
           ((uint32_t)dump_state[off + 2u] << 16) |
           ((uint32_t)dump_state[off + 3u] << 24);
}

static uint32_t ring_wrap(int64_t value, uint32_t ring) {
    value %= (int64_t)ring;
    if (value < 0)
        value += (int64_t)ring;
    return (uint32_t)value;
}

static void dump_fetch(uint32_t offset, uint32_t count) {
    uint32_t addr = dump_fetch_delta + offset;

    if (addr >= dump_ring)
        addr -= dump_ring;
    zw_scope_fetch_samples_generic((int32_t)addr, count);
    serial_wdt_feed();
}

static uint32_t dump_crc32_bytes(const uint8_t *p, uint32_t n) {
    uint32_t crc = 0xFFFFFFFFu;

    while (n-- != 0u)
        crc = container_crc32(crc, *p++);
    return crc ^ 0xFFFFFFFFu;
}

static void dump_copy_bytes(uint8_t *dst, const volatile uint8_t *src, uint32_t n) {
    while (n-- != 0u)
        *dst++ = *src++;
}

static void dump_state_snapshot(void) {
    dump_copy_bytes(dump_state, DUMP_SETTINGS, DUMP_SETTINGS_LEN);
    dump_copy_bytes(dump_state + DUMP_SETTINGS_LEN, scope_measurement_array_ch1, DUMP_MEAS_LEN);
    dump_copy_bytes(dump_state + DUMP_SETTINGS_LEN + DUMP_MEAS_LEN, scope_measurement_array_ch2, DUMP_MEAS_LEN);
}

static uint32_t dump_record_len(void) {
    uint32_t record = settings_u32(GS_RECORD_LEN);
    uint32_t ring = settings_u32(GS_RING_LEN);

    if (record > ring)
        record = ring;
    if (record > DUMP_SAMPLES_MAX)
        record = DUMP_SAMPLES_MAX;
    return record;
}

static void dump_window(uint32_t record) {
    uint32_t ring = settings_u32(GS_RING_LEN);
    uint64_t tb_ns;
    uint64_t win_ms;
    uint64_t win_samples;
    uint64_t span;
    uint64_t window_len;
    uint32_t rate;
    uint32_t pre;

    dump_window_len = 0u;
    dump_window_start = 0;
    dump_trigger = 0u;
    dump_record_start = 0u;
    dump_fetch_delta = 0u;
    if (ring == 0u)
        ring = record;
    dump_ring = (ring != 0u) ? ring : 1u;
    if (record == 0u)
        return;

    win_ms = (uint64_t)settings_u32(GS_WIN_ADDR_MS) |
             ((uint64_t)settings_u32(GS_WIN_ADDR_MS + 4u) << 32);
    win_samples = win_ms / 1000u;
    if (win_samples > 0x7FFFFFFFu)
        win_samples = 0x7FFFFFFFu;
    pre = settings_u32(GS_PRE_DEPTH);
    if (pre > record)
        pre = record;

    dump_fetch_delta = ring_wrap((int64_t)win_samples - (int64_t)pre, dump_ring);
    dump_record_start = ring_wrap((int64_t)settings_u32(GS_CURSOR) - (int64_t)pre, dump_ring);
    dump_window_start = (int32_t)pre - (int32_t)win_samples;
    dump_trigger = pre;

    tb_ns = (uint64_t)settings_u32(GS_TIMEBASE_NS_L) |
            ((uint64_t)settings_u32(GS_TIMEBASE_NS_H) << 32);
    rate = settings_u32(GS_SAMPLE_RATE_L);
    if (tb_ns == 0u || rate == 0u) {
        window_len = record;
    } else {
        span = tb_ns * DUMP_DIVISIONS;
        window_len = (span / 1000000000u) * rate +
                     ((span % 1000000000u) * rate) / 1000000000u;
        if (window_len == 0u)
            window_len = 1u;
        else if (window_len > 0xFFFFFFFFu)
            window_len = 0xFFFFFFFFu;
    }
    dump_window_len = (uint32_t)window_len;
}

static void dump_build_header(uint32_t flags, uint32_t samples,
                              uint32_t ch2, uint32_t crc_ch1,
                              uint32_t crc_ch2, uint32_t payload_len,
                              uint32_t encoding, uint32_t encoded_len,
                              uint32_t blocks) {
    uint32_t i;

    for (i = 0u; i < DUMP_HEADER_LEN; i++)
        dump_header[i] = 0u;
    dump_header[0] = (uint8_t)'Z';
    dump_header[1] = (uint8_t)'W';
    dump_header[2] = (uint8_t)'D';
    dump_header[3] = (uint8_t)'U';
    dump_header[4] = (uint8_t)'M';
    dump_header[5] = (uint8_t)'P';

    container_put_le32(dump_header + 8u, DUMP_VERSION);
    container_put_le32(dump_header + 12u, flags);
    container_put_le32(dump_header + 16u, samples);
    container_put_le32(dump_header + 20u, (ch2 != 0u) ? samples : 0u);
    container_put_le32(dump_header + 24u, 1u);
    container_put_le32(dump_header + 28u, settings_u32(GS_SAMPLE_RATE_L));
    container_put_le32(dump_header + 32u, settings_u32(GS_TIMEBASE_NS_L));
    container_put_le32(dump_header + 36u, settings_u32(GS_TIMEBASE_NS_H));
    container_put_le32(dump_header + 40u, crc_ch1);
    container_put_le32(dump_header + 44u, crc_ch2);
    container_put_le32(dump_header + 48u, payload_len);
    container_put_le32(dump_header + 52u, FRAME_MAX_DATA);
    container_put_le32(dump_header + 56u, blocks);
    container_put_le32(dump_header + 60u, settings_u32(GS_RING_LEN));

    container_put_le32(dump_header + 64u, DUMP_SETTINGS_LEN);
    container_put_le32(dump_header + 68u, dump_crc32_bytes(dump_state, DUMP_SETTINGS_LEN));
    container_put_le32(dump_header + 72u, DUMP_MEAS_LEN);
    container_put_le32(dump_header + 76u, dump_crc32_bytes(dump_state + DUMP_SETTINGS_LEN, DUMP_MEAS_LEN));
    container_put_le32(dump_header + 80u, DUMP_MEAS_LEN);
    container_put_le32(dump_header + 84u, dump_crc32_bytes(dump_state + DUMP_SETTINGS_LEN + DUMP_MEAS_LEN, DUMP_MEAS_LEN));
    container_put_le32(dump_header + 88u, DUMP_STATE_LEN);
    container_put_le32(dump_header + 92u, encoding);
    container_put_le32(dump_header + 96u, encoded_len);
    container_put_le32(dump_header + 100u, DUMP_CODEC_BLOCK);

    container_put_le32(dump_header + 104u, (uint32_t)dump_window_start);
    container_put_le32(dump_header + 108u, dump_window_len);
    container_put_le32(dump_header + 112u, dump_record_start);
    container_put_le32(dump_header + 116u, dump_trigger);
}

static void dump_analyse(uint32_t samples, uint32_t ch2,
                         uint32_t *crc_ch1, uint32_t *crc_ch2,
                         dump_codec_plan *plan1, dump_codec_plan *plan2) {
    uint32_t c1 = 0xFFFFFFFFu;
    uint32_t c2 = 0xFFFFFFFFu;
    uint32_t off;

    dump_codec_plan_init(plan1, samples);
    if (ch2 != 0u)
        dump_codec_plan_init(plan2, samples);

    for (off = 0u; off < samples; off += DUMP_CHUNK) {
        uint32_t len = samples - off;
        uint32_t i;

        if (len > DUMP_CHUNK)
            len = DUMP_CHUNK;
        dump_fetch(off, len);
        for (i = 0u; i < len; i++)
            c1 = container_crc32(c1, scope_acq_destination_ch1[i]);
        dump_codec_plan_samples(plan1, scope_acq_destination_ch1, len);
        if (ch2 != 0u) {
            for (i = 0u; i < len; i++)
                c2 = container_crc32(c2, scope_acq_destination_ch2[i]);
            dump_codec_plan_samples(plan2, scope_acq_destination_ch2, len);
        }
    }
    *crc_ch1 = c1 ^ 0xFFFFFFFFu;
    *crc_ch2 = c2 ^ 0xFFFFFFFFu;
}

static uint32_t dump_busy(void) {
    return (dump_state[GS_SCAN_MODE] != 0u &&
            dump_state[GS_ROLL_ENABLE] == 0u) ? 1u : 0u;
}

uint32_t fpga_dump_busy(void) {
    return (DUMP_SETTINGS[GS_SCAN_MODE] != 0u &&
            DUMP_SETTINGS[GS_ROLL_ENABLE] == 0u) ? 1u : 0u;
}

typedef struct {
    uint32_t channels;
    uint32_t samples;
    uint32_t channel;
    uint32_t index;
    uint32_t chunk_start;
    uint32_t chunk_len;
} dump_cursor;

static void dump_cursor_init(dump_cursor *c, uint32_t samples, uint32_t ch2) {
    c->channels = (ch2 != 0u) ? 2u : 1u;
    c->samples = samples;
    c->channel = 0u;
    c->index = 0u;
    c->chunk_start = 0u;
    c->chunk_len = 0u;
}

static const uint8_t *dump_channel_buffer(uint32_t channel) {
    return (channel == 0u) ? scope_acq_destination_ch1
                           : scope_acq_destination_ch2;
}

static uint8_t dump_next_byte(dump_cursor *c) {
    for (;;) {
        const uint8_t *buf;

        if (c->channel >= c->channels)
            return (uint8_t)DUMP_PAD;
        if (c->index < c->chunk_start + c->chunk_len) {
            uint8_t b;

            buf = dump_channel_buffer(c->channel);
            b = buf[c->index - c->chunk_start];
            c->index++;
            return b;
        }
        if (c->index >= c->samples) {
            c->channel++;
            c->index = 0u;
            c->chunk_start = 0u;
            c->chunk_len = 0u;
            continue;
        }
        {
            uint32_t len = c->samples - c->index;

            if (len > DUMP_CHUNK)
                len = DUMP_CHUNK;
            dump_fetch(c->index, len);
            c->chunk_start = c->index;
            c->chunk_len = len;
        }
    }
}

#define DUMP_ENC_BUF_LEN (1u + (DUMP_CODEC_BLOCK * 3u) / 2u)

typedef struct {
    const dump_codec_plan *plans;
    uint32_t channels;
    uint32_t channel;
    uint32_t index;
    uint32_t block;
    uint32_t chunk_start;
    uint32_t chunk_len;
    uint8_t prev;
    uint32_t enc_pos;
    uint32_t enc_len;
    uint8_t enc[DUMP_ENC_BUF_LEN];
} dump_encode_cursor;

static dump_encode_cursor dump_encoder;
static dump_cursor dump_raw_cursor;

static void dump_encode_init(dump_encode_cursor *c, const dump_codec_plan *plans, uint32_t channels) {
    c->plans = plans;
    c->channels = channels;
    c->channel = 0u;
    c->index = 0u;
    c->block = 0u;
    c->chunk_start = 0u;
    c->chunk_len = 0u;
    c->prev = 0u;
    c->enc_pos = 0u;
    c->enc_len = 0u;
}

static void dump_encode_fill(dump_encode_cursor *c) {
    const dump_codec_plan *p;
    const uint8_t *buf;
    uint32_t n;

    c->enc_pos = 0u;
    c->enc_len = 0u;
    while (c->channel < c->channels) {
        p = &c->plans[c->channel];
        if (c->index >= p->samples) {
            c->channel++;
            c->index = 0u;
            c->block = 0u;
            c->chunk_start = 0u;
            c->chunk_len = 0u;
            c->prev = 0u;
            continue;
        }
        n = p->samples - c->index;
        if (n > DUMP_CODEC_BLOCK)
            n = DUMP_CODEC_BLOCK;
        if (c->index < c->chunk_start ||
            c->index + n > c->chunk_start + c->chunk_len) {
            uint32_t len = p->samples - c->index;

            if (len > DUMP_CHUNK)
                len = DUMP_CHUNK;
            dump_fetch(c->index, len);
            c->chunk_start = c->index;
            c->chunk_len = len;
        }
        buf = dump_channel_buffer(c->channel) + (c->index - c->chunk_start);
        c->enc_len = dump_codec_encode_block(p->mode[c->block], c->prev, buf,
                                             n, c->enc);
        c->prev = buf[n - 1u];
        c->index += n;
        c->block++;
        return;
    }
}

static uint8_t dump_encode_next(dump_encode_cursor *c) {
    if (c->enc_pos >= c->enc_len)
        dump_encode_fill(c);
    if (c->enc_pos >= c->enc_len)
        return (uint8_t)DUMP_PAD;
    return c->enc[c->enc_pos++];
}

void fpga_dump_prepare(void) {
    uint32_t flags = 0u;
    uint32_t crc_ch1 = 0u;
    uint32_t crc_ch2 = 0u;
    uint32_t payload_len;
    uint32_t blocks;

    serial_wdt_feed();

    dump_state_snapshot();

    dump_samples = 0u;
    dump_ch2 = 0u;
    dump_encoding = 0u;
    dump_encoded_len = 0u;
    dump_window_len = 0u;
    dump_window_start = 0;
    dump_trigger = 0u;
    dump_record_start = 0u;
    dump_fetch_delta = 0u;

    if (dump_busy() == 0u) {
        uint32_t coded;

        dump_ch2 = (dump_state[GS_CH2_ENABLED] != 0u) ? 1u : 0u;
        dump_samples = dump_record_len();
        dump_window(dump_samples);
        flags |= DUMP_FLAG_FULL;
        if (dump_ch2 != 0u)
            flags |= DUMP_FLAG_CH2;
        dump_analyse(dump_samples, dump_ch2, &crc_ch1, &crc_ch2,
                     &dump_plan[0], &dump_plan[1]);

        payload_len = dump_samples * ((dump_ch2 != 0u) ? 2u : 1u);
        coded = dump_plan[0].encoded_len;
        if (dump_ch2 != 0u)
            coded += dump_plan[1].encoded_len;
        if (coded < payload_len) {
            dump_encoding = 1u;
            dump_encoded_len = coded;
        } else {
            dump_encoded_len = payload_len;
        }
    } else {
        flags |= DUMP_FLAG_BUSY;
        payload_len = 0u;
    }

    blocks = (DUMP_HEADER_LEN + dump_encoded_len + DUMP_STATE_LEN +
              FRAME_MAX_DATA - 1u) / FRAME_MAX_DATA;

    dump_build_header(flags, dump_samples, dump_ch2, crc_ch1, crc_ch2,
                      payload_len, dump_encoding, dump_encoded_len, blocks);

    dump_total_bytes = DUMP_HEADER_LEN + dump_encoded_len + DUMP_STATE_LEN;
}

uint32_t fpga_dump_total(void) {
    return dump_total_bytes;
}

void fpga_dump_start(void) {
    dump_offset = 0u;
    dump_cursor_init(&dump_raw_cursor, dump_samples, dump_ch2);
    dump_encode_init(&dump_encoder, dump_plan, (dump_ch2 != 0u) ? 2u : 1u);
}

void fpga_dump_read(uint8_t *dst, uint32_t len) {
    uint32_t payload_end = DUMP_HEADER_LEN + dump_encoded_len;

    while (len-- != 0u) {
        uint8_t b;

        if (dump_offset < DUMP_HEADER_LEN) {
            b = dump_header[dump_offset];
        } else if (dump_offset < payload_end) {
            b = (dump_encoding != 0u) ? dump_encode_next(&dump_encoder)
                                      : dump_next_byte(&dump_raw_cursor);
        } else {
            b = dump_state[dump_offset - payload_end];
        }
        *dst++ = b;
        dump_offset++;
    }
}
