#include "dump_codec.h"

static uint32_t codec_zigzag(int32_t d) {
    return (uint32_t)((d << 1) ^ (d >> 31));
}

void dump_codec_plan_init(dump_codec_plan *p, uint32_t samples) {
    uint32_t i;

    p->samples = samples;
    p->blocks = 0u;
    p->encoded_len = 0u;
    p->in_block = 0u;
    p->block_bits = 0u;
    p->block_samples = (samples > DUMP_CODEC_BLOCK) ? DUMP_CODEC_BLOCK : samples;
    p->prev = 0u;
    for (i = 0u; i < DUMP_CODEC_BLOCKS_MAX; i++)
        p->mode[i] = DUMP_CODEC_RAW;
}

void dump_codec_plan_samples(dump_codec_plan *p, const uint8_t *buf, uint32_t n) {
    uint32_t in_block = p->in_block;
    uint32_t bits = p->block_bits;
    uint32_t block_samples = p->block_samples;
    uint32_t blocks = p->blocks;
    uint32_t encoded = p->encoded_len;
    uint8_t prev = p->prev;

    while (n != 0u) {
        uint32_t take = block_samples - in_block;
        uint32_t i;

        if (take > n)
            take = n;
        for (i = 0u; i < take; i++) {
            uint8_t s = *buf++;
            int32_t d = (int32_t)s - (int32_t)prev;

            prev = s;
            bits += (codec_zigzag(d) < DUMP_CODEC_ESCAPE) ? 4u : 12u;
        }
        in_block += take;
        n -= take;

        if (in_block == block_samples) {
            uint32_t bytes = (bits + 7u) >> 3;

            if (bytes < block_samples) {
                p->mode[blocks] = DUMP_CODEC_DELTA;
                encoded += 1u + bytes;
            } else {
                p->mode[blocks] = DUMP_CODEC_RAW;
                encoded += 1u + block_samples;
            }
            blocks++;
            in_block = 0u;
            bits = 0u;
            {
                uint32_t left = p->samples - blocks * DUMP_CODEC_BLOCK;
                block_samples = (left > DUMP_CODEC_BLOCK) ? DUMP_CODEC_BLOCK : left;
            }
        }
    }

    p->in_block = in_block;
    p->block_bits = bits;
    p->block_samples = block_samples;
    p->blocks = blocks;
    p->encoded_len = encoded;
    p->prev = prev;
}

uint32_t dump_codec_encode_block(uint8_t mode, uint8_t prev, const uint8_t *in, uint32_t n, uint8_t *out) {
    uint32_t pos = 0u;
    uint32_t i;
    uint32_t acc = 0u;
    uint32_t nbits = 0u;

    out[pos++] = mode;
    if (mode == DUMP_CODEC_RAW) {
        for (i = 0u; i < n; i++)
            out[pos++] = in[i];
        return pos;
    }

    for (i = 0u; i < n; i++) {
        uint8_t s = in[i];
        int32_t d = (int32_t)s - (int32_t)prev;
        uint32_t z = codec_zigzag(d);

        prev = s;
        if (z < DUMP_CODEC_ESCAPE) {
            acc = (acc << 4) | z;
            nbits += 4u;
        } else {
            acc = (acc << 4) | DUMP_CODEC_ESCAPE;
            nbits += 4u;
            while (nbits >= 8u) {
                nbits -= 8u;
                out[pos++] = (uint8_t)(acc >> nbits);
            }
            acc = (acc << 8) | s;
            nbits += 8u;
        }
        while (nbits >= 8u) {
            nbits -= 8u;
            out[pos++] = (uint8_t)(acc >> nbits);
        }
        if (nbits != 0u)
            acc &= (1u << nbits) - 1u;
    }
    if (nbits != 0u)
        out[pos++] = (uint8_t)(acc << (8u - nbits));
    return pos;
}
