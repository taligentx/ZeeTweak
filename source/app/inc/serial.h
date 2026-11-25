// Serial protocol setup

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_mask_irqs(void);
uint32_t serial_rx_count(void);
uint8_t serial_getc(void);
void serial_drain(void);
void serial_putc(uint8_t c);
void serial_wdt_feed(void);
uint32_t serial_baud(void);
uint32_t serial_baud_valid(uint32_t rate);
int serial_set_baud(uint32_t rate);

#endif
