#include "frame.h"
#include "serial.h"

#define PARSER_SYNC0   0u
#define PARSER_SYNC1   1u
#define PARSER_HEADER  2u
#define PARSER_PAYLOAD 3u
#define PARSER_CRC     4u

static struct {
    uint8_t state;
    uint8_t header_pos;
    uint8_t header[6];  // version, type, seq, len
    uint16_t len;
    uint16_t pos;
    uint16_t crc;
    uint16_t crc_rx;
    uint8_t crc_pos;
    uint8_t over_limit;
    uint8_t payload[FRAME_MAX_CONTROL];
} parser;

uint16_t frame_crc16(uint16_t crc, uint8_t b) {
    uint32_t i;

    crc = (uint16_t)(crc ^ ((uint16_t)b << 8));
    for (i = 0u; i < 8u; i++) {
        if (crc & 0x8000u)
            crc = (uint16_t)((crc << 1) ^ 0x1021u);
        else
            crc = (uint16_t)(crc << 1);
    }
    return crc;
}

static void put_le16(uint8_t *p, uint16_t v) {
    p[0] = (uint8_t)(v & 0xFFu);
    p[1] = (uint8_t)(v >> 8);
}

void frame_send(uint8_t type, uint16_t seq, const uint8_t *payload, uint16_t len) {
    uint8_t header[6];
    uint16_t crc = 0xFFFFu;
    uint16_t i;

    header[0] = FRAME_VERSION;
    header[1] = type;
    put_le16(header + 2, seq);
    put_le16(header + 4, len);
    for (i = 0u; i < 6u; i++)
        crc = frame_crc16(crc, header[i]);
    for (i = 0u; i < len; i++)
        crc = frame_crc16(crc, payload[i]);

    serial_putc(FRAME_SYNC0);
    serial_putc(FRAME_SYNC1);
    for (i = 0u; i < 6u; i++)
        serial_putc(header[i]);
    for (i = 0u; i < len; i++)
        serial_putc(payload[i]);
    serial_putc((uint8_t)(crc & 0xFFu));
    serial_putc((uint8_t)(crc >> 8));
}

void frame_parser_reset(void) {
    parser.state = PARSER_SYNC0;
    parser.header_pos = 0u;
    parser.len = 0u;
    parser.pos = 0u;
    parser.crc = 0xFFFFu;
    parser.crc_rx = 0u;
    parser.crc_pos = 0u;
    parser.over_limit = 0u;
}

uint8_t frame_parser_busy(void) {
    return (parser.state != PARSER_SYNC0) ? 1u : 0u;
}

frame_parse_result frame_parser_feed(uint8_t b, frame_view *out) {
    uint16_t i;

    switch (parser.state) {
    case PARSER_SYNC0:
        if (b == FRAME_SYNC0)
            parser.state = PARSER_SYNC1;
        return FRAME_PARSE_NONE;

    case PARSER_SYNC1:
        if (b == FRAME_SYNC1) {
            parser.state = PARSER_HEADER;
            parser.header_pos = 0u;
        } else if (b != FRAME_SYNC0) {
            parser.state = PARSER_SYNC0;
        }
        return FRAME_PARSE_NONE;

    case PARSER_HEADER:
        parser.header[parser.header_pos] = b;
        parser.header_pos++;
        if (parser.header_pos < 6u)
            return FRAME_PARSE_NONE;

        parser.len = (uint16_t)parser.header[4] |
                     ((uint16_t)parser.header[5] << 8);
        if (parser.len > FRAME_MAX_DATA) {
            frame_parser_reset();
            return FRAME_PARSE_NONE;
        }
        parser.crc = 0xFFFFu;
        for (i = 0u; i < 6u; i++)
            parser.crc = frame_crc16(parser.crc, parser.header[i]);
        parser.pos = 0u;
        parser.over_limit = (parser.len > FRAME_MAX_CONTROL) ? 1u : 0u;
        parser.crc_rx = 0u;
        parser.crc_pos = 0u;
        parser.state = (parser.len == 0u) ? PARSER_CRC : PARSER_PAYLOAD;
        return FRAME_PARSE_NONE;

    case PARSER_PAYLOAD:
        if (parser.over_limit == 0u)
            parser.payload[parser.pos] = b;
        parser.crc = frame_crc16(parser.crc, b);
        parser.pos++;
        if (parser.pos < parser.len)
            return FRAME_PARSE_NONE;
        parser.state = PARSER_CRC;
        return FRAME_PARSE_NONE;

    case PARSER_CRC:
        parser.crc_rx |= (uint16_t)b << (8u * parser.crc_pos);
        parser.crc_pos++;
        if (parser.crc_pos < 2u)
            return FRAME_PARSE_NONE;
        {
            uint16_t crc = parser.crc;
            uint16_t crc_rx = parser.crc_rx;
            uint8_t version = parser.header[0];
            uint8_t type = parser.header[1];
            uint16_t seq = (uint16_t)parser.header[2] |
                           ((uint16_t)parser.header[3] << 8);
            uint16_t len = parser.len;
            uint8_t over = parser.over_limit;

            out->version = version;
            out->type = type;
            out->seq = seq;
            out->len = len;
            if (over == 0u) {
                for (i = 0u; i < len; i++)
                    out->payload[i] = parser.payload[i];
            }
            frame_parser_reset();

            if (crc_rx != crc)
                return FRAME_PARSE_NONE;
            if (version != FRAME_VERSION)
                return FRAME_PARSE_BAD_VERSION;
            if (over != 0u)
                return FRAME_PARSE_BAD_LENGTH;
            return FRAME_PARSE_FRAME;
        }

    default:
        frame_parser_reset();
        return FRAME_PARSE_NONE;
    }
}
