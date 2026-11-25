// FPGA buffer waveform dump transfer

#ifndef DUMP_CODEC_H
#define DUMP_CODEC_H

#include <stdint.h>

#define DUMP_CODEC_BLOCK       1000u
#define DUMP_CODEC_BLOCKS_MAX  60u
#define DUMP_CODEC_RAW         0u
#define DUMP_CODEC_DELTA       1u
#define DUMP_CODEC_ESCAPE      15u

typedef struct {
    uint32_t samples;
    uint32_t blocks;
    uint32_t encoded_len;
    uint32_t in_block;
    uint32_t block_bits;
    uint32_t block_samples;
    uint8_t prev;
    uint8_t mode[DUMP_CODEC_BLOCKS_MAX];
} dump_codec_plan;

void dump_codec_plan_init(dump_codec_plan *p, uint32_t samples);
void dump_codec_plan_samples(dump_codec_plan *p, const uint8_t *buf, uint32_t n);
uint32_t dump_codec_encode_block(uint8_t mode, uint8_t prev, const uint8_t *in, uint32_t n, uint8_t *out);

#endif
