#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>

uint32_t container_crc32(uint32_t crc, uint8_t b);
void container_put_le32(uint8_t *p, uint32_t v);

#endif
