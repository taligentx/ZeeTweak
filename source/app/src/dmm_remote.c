// Relays DMM data as FS9922 data @ 2400baud

#include "dmm_remote.h"
#include "frame.h"
#include "serial.h"
#include "zw_api.h"

#define DMM_RX_LEN 10u
#define DMM_DATA_LEN 8u
#define DMM_NIBBLES (2u * DMM_DATA_LEN)
#define FS9922_LEN 14u
#define F_SIGN 0u                    /* '+' or '-' */
#define F_DIGIT 1u                   /* four ASCII digits, left to right */
#define F_SPACE 5u                   /* ' ' */
#define F_POINT 6u                   /* '0' '1' '2' '4' */
#define F_SB1 7u                     /* AUTO DC AC REL HOLD BPN */
#define F_SB2 8u                     /* Z1 Z2 MAX MIN APO Bat n Z3 */
#define F_SB3 9u                     /* u m k M Beep Diode % Z4 */
#define F_SB4 10u                    /* V A Ohm hFE Hz F C F */
#define F_BAR 11u
#define F_CR 12u
#define F_LF 13u
#define FS9922_BAUD 2400u
#define SETTINGS_DMM_MODE_OFF 0x12Eu
#define SETTINGS_DMM_MODE (((const volatile uint8_t *)global_settings)[SETTINGS_DMM_MODE_OFF])
#define N_MARK 0u                    /* (RS232 3, see Z3) Auto 2, DC 1, AC 0 */
#define N_UNIT1 9u                   /* Diode 3, k 2, n 1, u 0 */
#define N_UNIT2 10u                  /* Beep 3, M 2, % 1, m 0 */
#define N_MODE1 11u                  /* Hold 3, Rel 2, Ohm 1, Farads 0 */
#define N_MODE2 12u                  /* Low battery 3, Hz 2, Volts 1, Amps 0 */
#define N_TEMP 13u                   /* UD1 3, UD2 2, Celsius 1, Fahrenheit 0 */
#define N_MAXMIN 14u                 /* Max 3, Min-Max 2, Min 1, APO 0 */

static int read_stable_frame(uint8_t *frame) {
    uint8_t check[DMM_RX_LEN];
    uint32_t i;

    for (i = 0u; i < DMM_RX_LEN; i++) {
        frame[i] = dmm_rx_buffer[i];
    }
    for (i = 0u; i < DMM_RX_LEN; i++) {
        check[i] = dmm_rx_buffer[i];
    }
    for (i = 0u; i < DMM_RX_LEN; i++) {
        if (frame[i] != check[i]) {
            return 0;
        }
    }
    return frame[0] == 0x5Au && frame[1] == 0xA5u;
}

static uint8_t nibble_bit(const uint8_t *nibble, uint8_t index, uint8_t bit) {
    return (uint8_t)((nibble[index] >> bit) & 1u);
}

static uint8_t digit_from_code(uint8_t code) {
    if (code < 10u) {
        return (uint8_t)('0' + code);
    }
    return (code == 0xFFu) ? '0' : 0u;
}

static void emit_value(uint8_t *out) {
    static const uint8_t points[] = { '1', '2', '4' };
    uint8_t code[4];
    uint32_t value;
    uint8_t i;

    code[0] = dmm_digit_3;
    code[1] = dmm_digit_2;
    code[2] = dmm_digit_1;
    code[3] = dmm_digit_0;
    value = (uint32_t)dmm_measurement_value;

    out[F_SIGN] = (dmm_dp_0[3] != 0u) ? '-' : '+';
    out[F_POINT] = '0';
    for (i = 0u; i < 3u; i++) {
        if (out[F_POINT] == '0' && dmm_dp_0[2u - i] != 0u) {
            out[F_POINT] = points[i];
        }
    }

    if (dmm_mode_index != 1u && value <= 9999u &&
        code[0] < 10u && code[1] < 10u && code[2] < 10u && code[3] < 10u) {
        out[F_DIGIT] = (uint8_t)('0' + value / 1000u);
        out[F_DIGIT + 1u] = (uint8_t)('0' + (value % 1000u) / 100u);
        out[F_DIGIT + 2u] = (uint8_t)('0' + (value % 100u) / 10u);
        out[F_DIGIT + 3u] = (uint8_t)('0' + (value % 10u));
        return;
    }

    for (i = 0u; i < 4u; i++) {
        out[F_DIGIT + i] = digit_from_code(code[i]);
        if (out[F_DIGIT + i] == 0u) {
            out[F_DIGIT] = '?';
            out[F_DIGIT + 1u] = '0';
            out[F_DIGIT + 2u] = ':';
            out[F_DIGIT + 3u] = '?';
            out[F_POINT] = '0';
            return;
        }
    }
}

static void build_packet(const uint8_t *nibble, uint8_t *out) {
    uint8_t sb1 = 0u, sb2 = 0u, sb3 = 0u, sb4 = 0u;

    out[F_SPACE] = ' ';
    out[F_BAR] = 0u;
    out[F_CR] = '\r';
    out[F_LF] = '\n';
    emit_value(out);

    if (nibble_bit(nibble, N_MARK, 2) != 0u) {
        sb1 |= 0x20u;                /* AUTO */
    }
    if (nibble_bit(nibble, N_MARK, 1) != 0u) {
        sb1 |= 0x10u;                /* DC */
    }
    if (nibble_bit(nibble, N_MARK, 0) != 0u) {
        sb1 |= 0x08u;                /* AC */
    }
    if (nibble_bit(nibble, N_MODE1, 2) != 0u) {
        sb1 |= 0x04u;                /* REL */
    }
    if (nibble_bit(nibble, N_MODE1, 3) != 0u) {
        sb1 |= 0x02u;                /* HOLD */
    }

    if (nibble_bit(nibble, N_UNIT1, 2) != 0u) {
        sb3 |= 0x20u;                /* k */
    } else if (nibble_bit(nibble, N_UNIT1, 1) != 0u) {
        sb2 |= 0x02u;                /* n */
    } else if (nibble_bit(nibble, N_UNIT1, 0) != 0u) {
        sb3 |= 0x80u;                /* u */
    } else if (nibble_bit(nibble, N_UNIT2, 2) != 0u) {
        sb3 |= 0x10u;                /* M */
    } else if (nibble_bit(nibble, N_UNIT2, 0) != 0u) {
        sb3 |= 0x40u;                /* m */
    }

    if (nibble_bit(nibble, N_MODE1, 1) != 0u) {
        sb4 |= 0x20u;                /* ohm */
    } else if (nibble_bit(nibble, N_MODE1, 0) != 0u) {
        sb4 |= 0x04u;                /* farads */
    } else if (nibble_bit(nibble, N_MODE2, 1) != 0u) {
        sb4 |= 0x80u;                /* volts */
    } else if (nibble_bit(nibble, N_MODE2, 0) != 0u) {
        sb4 |= 0x40u;                /* amps */
    } else if (nibble_bit(nibble, N_MODE2, 2) != 0u) {
        sb4 |= 0x08u;                /* Hz */
    } else if (nibble_bit(nibble, N_UNIT2, 1) != 0u) {
        sb3 |= 0x02u;                /* % */
    } else if (nibble_bit(nibble, N_TEMP, 1) != 0u) {
        sb4 |= 0x02u;                /* Celsius */
    } else if (nibble_bit(nibble, N_TEMP, 0) != 0u) {
        sb4 |= 0x01u;                /* Fahrenheit */
    }

    if (nibble_bit(nibble, N_UNIT1, 3) != 0u) {
        sb3 |= 0x04u;                /* diode */
    }
    if (nibble_bit(nibble, N_UNIT2, 3) != 0u) {
        sb3 |= 0x08u;                /* beep */
    }
    if (nibble_bit(nibble, N_MODE2, 3) != 0u) {
        sb2 |= 0x04u;                /* low battery */
    }
    if (nibble_bit(nibble, N_MAXMIN, 3) != 0u) {
        sb2 |= 0x20u;                /* MAX */
    }
    if (nibble_bit(nibble, N_MAXMIN, 1) != 0u) {
        sb2 |= 0x10u;                /* MIN */
    }
    if (nibble_bit(nibble, N_MAXMIN, 0) != 0u) {
        sb2 |= 0x08u;                /* auto power-off */
    }

    sb2 |= 0x01u;                    /* Z3 = RS232, by board construction */
    if (nibble_bit(nibble, N_TEMP, 3) != 0u) {
        sb2 |= 0x80u;                /* Z1 = UD1 */
    }
    if (nibble_bit(nibble, N_TEMP, 2) != 0u) {
        sb2 |= 0x40u;                /* Z2 = UD2 */
    }
    if (nibble_bit(nibble, N_MAXMIN, 2) != 0u) {
        sb3 |= 0x01u;                /* Z4 = min-max */
    }

    out[F_SB1] = sb1;
    out[F_SB2] = sb2;
    out[F_SB3] = sb3;
    out[F_SB4] = sb4;
}

#define RELAY_BAUD_HELD 1u
static uint32_t relay_baud_saved;

static void relay_set_baud(uint32_t rate) {
    (void)serial_set_baud(rate);
    serial_drain();
    frame_parser_reset();
}

static void relay_use_fs9922_baud(void) {
    uint32_t rate;

    if (relay_baud_saved != 0u) {
        return;
    }
    rate = serial_baud();
    if (rate == FS9922_BAUD) {
        relay_baud_saved = RELAY_BAUD_HELD;
        return;
    }
    relay_baud_saved = rate;
    relay_set_baud(FS9922_BAUD);
}

void dmm_remote_baud_poll(void)
{
    uint32_t rate = relay_baud_saved;

    if (rate == 0u || rate == RELAY_BAUD_HELD || SETTINGS_DMM_MODE != 0u) {
        return;
    }
    relay_baud_saved = 0u;

    if (serial_baud() == FS9922_BAUD) {
        relay_set_baud(rate);
    }
}

uint32_t dmm_remote_flush(uint32_t *timer) {
    uint8_t frame[DMM_RX_LEN];
    uint8_t nibble[DMM_NIBBLES];
    uint8_t packet[FS9922_LEN];
    uint32_t i;

    if (zw_timer_check(timer) == 0u) {
        return 0u;
    }
    if (!read_stable_frame(frame)) {
        return 0u;
    }

    for (i = 0u; i < DMM_DATA_LEN; i++) {
        nibble[i * 2u] = frame[2u + i] & 0x0Fu;
        nibble[i * 2u + 1u] = frame[2u + i] >> 4;
    }
    build_packet(nibble, packet);

    relay_use_fs9922_baud();
    for (i = 0u; i < FS9922_LEN; i++) {
        serial_putc(packet[i]);
    }

    return 0u;
}
