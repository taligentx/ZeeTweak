// Serial protocol

#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define FRAME_SYNC0        0xA5u
#define FRAME_SYNC1        0x5Au
#define FRAME_VERSION      1u
#define FRAME_MAX_CONTROL  64u
#define FRAME_MAX_DATA     1024u
#define FRAME_PERSIST_REQ_LEN 8u

enum {
    // Host to scope
    FRAME_HELLO       = 0x01,
    FRAME_SET_BAUD    = 0x02,
    FRAME_SCREENSHOT  = 0x10,
    FRAME_DUMP        = 0x11,
    FRAME_PERSIST     = 0x17,
    FRAME_DATA_ACK    = 0x40,
    FRAME_ABORT       = 0x41,
    // Scope to host
    FRAME_INFO        = 0x81,
    FRAME_BAUD_STATUS = 0x82,
    FRAME_SHOT_BEGIN  = 0x90,
    FRAME_DUMP_BEGIN  = 0x91,
    FRAME_PERSIST_BEGIN = 0x97,
    FRAME_DATA        = 0xC0,
    FRAME_ERROR       = 0xFF
};

enum {
    FRAME_OK           = 0,
    FRAME_BAD_PARAM    = 1,
    FRAME_BAD_RATE     = 2,
    FRAME_BUSY         = 3,
    FRAME_UNKNOWN_TYPE = 4,
    FRAME_BAD_LENGTH   = 5,
    FRAME_BAD_VERSION  = 6,
    FRAME_ABORTED      = 7,
    FRAME_CRC_ERROR    = 8,
    FRAME_TIMEOUT      = 9,
    FRAME_INTERNAL     = 10,
    FRAME_OUT_OF_ORDER = 11,
    FRAME_DROPPED      = 12
};

typedef struct {
    uint8_t version;
    uint8_t type;
    uint16_t seq;
    uint16_t len;
    uint8_t payload[FRAME_MAX_CONTROL];
} frame_view;

typedef void (*frame_handler)(const frame_view *f);

typedef enum {
    FRAME_PARSE_NONE = 0,
    FRAME_PARSE_FRAME,
    FRAME_PARSE_BAD_VERSION,
    FRAME_PARSE_BAD_LENGTH
} frame_parse_result;

uint16_t frame_crc16(uint16_t crc, uint8_t b);
void frame_send(uint8_t type, uint16_t seq, const uint8_t *payload, uint16_t len);
uint8_t frame_parser_busy(void);
void frame_parser_reset(void);
frame_parse_result frame_parser_feed(uint8_t b, frame_view *out);

#endif
