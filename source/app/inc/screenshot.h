// Sends a screenshot of the current LCD display

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <stdint.h>

#define SCREENSHOT_WIDTH        320u
#define SCREENSHOT_HEIGHT       240u
#define SCREENSHOT_FB_LEN       (SCREENSHOT_WIDTH * SCREENSHOT_HEIGHT)
#define SCREENSHOT_PAL_LEN      512u
#define SCREENSHOT_VERSION      7u
#define SCREENSHOT_HEADER_LEN   64u
#define SCREENSHOT_PAYLOAD_LEN  (SCREENSHOT_PAL_LEN + SCREENSHOT_FB_LEN)
#define SCREENSHOT_MODE_RAW     0u
#define SCREENSHOT_MODE_RLE     1u

void screenshot_prepare(void);
uint32_t screenshot_total(void);
void screenshot_start(void);
void screenshot_read(uint8_t *dst, uint32_t len);

#endif
