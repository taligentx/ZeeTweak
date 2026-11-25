#include "serial.h"
#include "zw_api.h"
#include "wm_regs.h"

#define SERIAL_UART ((USART_TypeDef *)(uintptr_t)UART0_BASE)
#define SERIAL_TX_TIMEOUT_MS 100u
#define SERIAL_TX_FIFO_FULL  32u
#define SERIAL_UART_IRQ_MASK 0x1FFu

static uint32_t uart_baud = 115200u;

uint32_t serial_baud(void) {
    return uart_baud;
}

uint32_t serial_baud_valid(uint32_t rate) {
    switch (rate) {
    case 2400u:
    case 4800u:
    case 9600u:
    case 19200u:
    case 38400u:
    case 57600u:
    case 115200u:
    case 230400u:
    case 460800u:
    case 921600u:
    case 1000000u:
    case 1250000u:
    case 1500000u:
    case 2000000u:
        return 1u;
    default:
        return 0u;
    }
}

static uint32_t baud_divisor(uint32_t rate) {
    return (APB_CLK / (16u * rate) - 1u) |
           (((APB_CLK % (rate * 16u)) * 16u / (rate * 16u)) << 16);
}

int serial_set_baud(uint32_t rate) {
    uint32_t flush_ms;
    uint32_t start;

    if (serial_baud_valid(rate) == 0u)
        return -1;

    flush_ms = ((uint32_t)(SERIAL_TX_FIFO_FULL + 5u) * 10u * 1000u) / uart_baud + 20u;
    start = HAL_GetTick();
    while ((SERIAL_UART->FIFOS & UART_FIFOS_TFC_Msk) != 0u &&
           (uint32_t)(HAL_GetTick() - start) < flush_ms)
        serial_wdt_feed();
    HAL_Delay(30000u / uart_baud + 1u);

    SERIAL_UART->BAUDR = baud_divisor(rate);
    uart_baud = rate;
    return 0;
}

void serial_mask_irqs(void) {
    SERIAL_UART->INTM = SERIAL_UART_IRQ_MASK;
    SERIAL_UART->INTS = SERIAL_UART_IRQ_MASK;
}

uint32_t serial_rx_count(void) {
    return (SERIAL_UART->FIFOS & UART_FIFOS_RFC_Msk) >> UART_FIFOS_RFC_Pos;
}

uint8_t serial_getc(void) {
    return (uint8_t)SERIAL_UART->RDW;
}

void serial_drain(void) {
    while (serial_rx_count() != 0u)
        (void)serial_getc();
}

void serial_putc(uint8_t c) {
    uint32_t start = HAL_GetTick();

    while ((SERIAL_UART->FIFOS & UART_FIFOS_TFC_Msk) >=
           SERIAL_TX_FIFO_FULL) {
        if ((uint32_t)(HAL_GetTick() - start) >= SERIAL_TX_TIMEOUT_MS)
            break;
        serial_wdt_feed();
    }
    SERIAL_UART->TDW = c;
}

void serial_wdt_feed(void) {
    if (hwdg.Instance != 0)
        ((WDG_TypeDef *)hwdg.Instance)->CLR = 1u;
}
