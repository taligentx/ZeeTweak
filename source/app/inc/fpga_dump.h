// FPGA buffer waveform dump

#ifndef FPGA_DUMP_H
#define FPGA_DUMP_H

#include <stdint.h>

void fpga_dump_prepare(void);
uint32_t fpga_dump_total(void);
void fpga_dump_start(void);
void fpga_dump_read(uint8_t *dst, uint32_t len);
uint32_t fpga_dump_busy(void);

#endif
