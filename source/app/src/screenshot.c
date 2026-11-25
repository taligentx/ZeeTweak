#include "screenshot.h"
#include "container.h"
#include "frame.h"
#include "serial.h"
#include "zw_api.h"

#define SCREENSHOT_FB   ((const uint8_t *)framebuffer)
#define SCREENSHOT_PAL  ((const uint8_t *)scope_palette_RAM)

static uint8_t screenshot_header[SCREENSHOT_HEADER_LEN];
static uint32_t screenshot_fb_crc;
static uint32_t screenshot_pal_crc;
static uint32_t screenshot_mode;
static uint32_t screenshot_total_bytes;
static uint32_t screenshot_offset;

typedef struct {
    const uint8_t *next;
    uint32_t left;
    uint8_t segment;
} payload_cursor;

static payload_cursor screenshot_payload;

static void payload_init(payload_cursor *c, const uint8_t *pal) {
    c->next = pal;
    c->left = SCREENSHOT_PAL_LEN;
    c->segment = 0u;
}

static void payload_next(payload_cursor *c, const uint8_t *fb) {
    c->next++;
    c->left--;
    if (c->left == 0u && c->segment == 0u) {
        c->next = fb;
        c->left = SCREENSHOT_FB_LEN;
        c->segment = 1u;
    }
}

static uint32_t screenshot_rle_size(const uint8_t *fb, const uint8_t *pal) {
    payload_cursor c;
    uint32_t n = 0u;
    uint32_t run = 0u;
    uint32_t seen = 0u;
    uint32_t feed_at = 0x1000u;
    uint8_t v = 0u;

    payload_init(&c, pal);
    while (c.left != 0u && n < SCREENSHOT_PAYLOAD_LEN) {
        uint8_t b = *c.next;

        if (run != 0u && b == v && run < 255u) {
            run++;
        } else {
            if (run != 0u)
                n += 2u;
            v = b;
            run = 1u;
        }
        payload_next(&c, fb);
        seen++;
        if (seen >= feed_at) {
            feed_at = seen + 0x1000u;
            serial_wdt_feed();
        }
    }
    if (run != 0u)
        n += 2u;
    return n;
}

static payload_cursor screenshot_encoder;
static uint32_t screenshot_encoder_phase;
static uint8_t screenshot_encoder_value;

static void screenshot_encoder_reset(const uint8_t *pal) {
    payload_init(&screenshot_encoder, pal);
    screenshot_encoder_phase = 0u;
    screenshot_encoder_value = 0u;
}

static uint8_t screenshot_encoder_next(const uint8_t *fb) {
    if (screenshot_encoder_phase != 0u) {
        screenshot_encoder_phase = 0u;
        return screenshot_encoder_value;
    }
    {
        uint8_t v = *screenshot_encoder.next;
        uint32_t run = 0u;

        while (screenshot_encoder.left != 0u && run < 255u &&
               *screenshot_encoder.next == v) {
            payload_next(&screenshot_encoder, fb);
            run++;
        }
        screenshot_encoder_value = v;
        screenshot_encoder_phase = 1u;
        return (uint8_t)run;
    }
}

void screenshot_prepare(void) {
    const uint8_t *fb = SCREENSHOT_FB;
    const uint8_t *pal = SCREENSHOT_PAL;
    uint32_t crc;
    uint32_t encoded_len;
    uint32_t mode;
    uint32_t blocks;
    uint32_t i;

    serial_wdt_feed();

    for (i = 0u; i < SCREENSHOT_HEADER_LEN; i++)
        screenshot_header[i] = 0u;
    screenshot_header[0] = (uint8_t)'Z';
    screenshot_header[1] = (uint8_t)'W';
    screenshot_header[2] = (uint8_t)'S';
    screenshot_header[3] = (uint8_t)'H';
    screenshot_header[4] = (uint8_t)'O';
    screenshot_header[5] = (uint8_t)'T';

    crc = 0xFFFFFFFFu;
    for (i = 0u; i < SCREENSHOT_PAL_LEN; i++) {
        crc = container_crc32(crc, pal[i]);
        if ((i & 0xFFFu) == 0u)
            serial_wdt_feed();
    }
    screenshot_pal_crc = crc ^ 0xFFFFFFFFu;

    crc = 0xFFFFFFFFu;
    for (i = 0u; i < SCREENSHOT_FB_LEN; i++) {
        crc = container_crc32(crc, fb[i]);
        if ((i & 0xFFFu) == 0u)
            serial_wdt_feed();
    }
    screenshot_fb_crc = crc ^ 0xFFFFFFFFu;

    encoded_len = screenshot_rle_size(fb, pal);
    if (encoded_len < SCREENSHOT_PAYLOAD_LEN) {
        mode = SCREENSHOT_MODE_RLE;
    } else {
        mode = SCREENSHOT_MODE_RAW;
        encoded_len = SCREENSHOT_PAYLOAD_LEN;
    }
    blocks = (SCREENSHOT_HEADER_LEN + encoded_len + FRAME_MAX_DATA - 1u) /
             FRAME_MAX_DATA;

    container_put_le32(screenshot_header + 8u, SCREENSHOT_VERSION);
    container_put_le32(screenshot_header + 12u, SCREENSHOT_WIDTH);
    container_put_le32(screenshot_header + 16u, SCREENSHOT_HEIGHT);
    container_put_le32(screenshot_header + 20u, SCREENSHOT_FB_LEN);
    container_put_le32(screenshot_header + 24u, SCREENSHOT_PAL_LEN);
    container_put_le32(screenshot_header + 28u, SCREENSHOT_PAYLOAD_LEN);
    container_put_le32(screenshot_header + 32u, screenshot_fb_crc);
    container_put_le32(screenshot_header + 36u, screenshot_pal_crc);
    container_put_le32(screenshot_header + 40u, FRAME_MAX_DATA);
    container_put_le32(screenshot_header + 44u, blocks);
    container_put_le32(screenshot_header + 48u, mode);
    container_put_le32(screenshot_header + 52u, encoded_len);

    screenshot_mode = mode;
    screenshot_total_bytes = SCREENSHOT_HEADER_LEN + encoded_len;
}

uint32_t screenshot_total(void) {
    return screenshot_total_bytes;
}

void screenshot_start(void) {
    screenshot_offset = 0u;
    payload_init(&screenshot_payload, SCREENSHOT_PAL);
    screenshot_encoder_reset(SCREENSHOT_PAL);
}

void screenshot_read(uint8_t *dst, uint32_t len) {
    const uint8_t *fb = SCREENSHOT_FB;

    while (len-- != 0u) {
        if (screenshot_offset < SCREENSHOT_HEADER_LEN) {
            *dst++ = screenshot_header[screenshot_offset];
        } else if (screenshot_mode == SCREENSHOT_MODE_RAW) {
            *dst++ = *screenshot_payload.next;
            payload_next(&screenshot_payload, fb);
        } else {
            *dst++ = screenshot_encoder_next(fb);
        }
        screenshot_offset++;
    }
}
