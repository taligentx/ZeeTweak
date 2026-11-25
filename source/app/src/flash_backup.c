#include "flash_backup.h"
#include "container.h"
#include "serial.h"

#define FLASH_BACKUP_FEED   0x1000u
#define HDR_MAGIC   0u
#define HDR_VERSION 8u
#define HDR_ADDR    12u
#define HDR_LEN     16u
#define HDR_FBASE   20u
#define HDR_FSIZE   24u
#define HDR_CRC     28u

static uint8_t header[FLASH_BACKUP_HEADER_LEN];
static uint32_t range_addr;
static uint32_t range_len;
static uint32_t total_bytes;
static uint32_t offset;

static const volatile uint8_t *flash_window(uint32_t addr) {
    return (const volatile uint8_t *)(uintptr_t)addr;
}

uint32_t flash_backup_range(uint32_t addr, uint32_t len) {
    if (len == 0u)
        return 0u;
    if (addr < FLASH_BACKUP_BASE || addr >= FLASH_BACKUP_LIMIT)
        return 0u;
    if (len > FLASH_BACKUP_LIMIT - addr)
        return 0u;

    range_addr = addr;
    range_len = len;
    return 1u;
}

void flash_backup_prepare(void) {
    const volatile uint8_t *src = flash_window(range_addr);
    uint32_t crc = 0xFFFFFFFFu;
    uint32_t i;

    for (i = 0u; i < FLASH_BACKUP_HEADER_LEN; i++)
        header[i] = 0u;
    header[HDR_MAGIC + 0u] = (uint8_t)'Z';
    header[HDR_MAGIC + 1u] = (uint8_t)'W';
    header[HDR_MAGIC + 2u] = (uint8_t)'F';
    header[HDR_MAGIC + 3u] = (uint8_t)'L';
    header[HDR_MAGIC + 4u] = (uint8_t)'S';
    header[HDR_MAGIC + 5u] = (uint8_t)'H';

    container_put_le32(header + HDR_VERSION, FLASH_BACKUP_VERSION);
    container_put_le32(header + HDR_ADDR, range_addr);
    container_put_le32(header + HDR_LEN, range_len);
    container_put_le32(header + HDR_FBASE, FLASH_BACKUP_FLASH_BASE);
    container_put_le32(header + HDR_FSIZE, FLASH_BACKUP_FLASH_SIZE);

    for (i = 0u; i < range_len; i++) {
        crc = container_crc32(crc, src[i]);
        if ((i & (FLASH_BACKUP_FEED - 1u)) == 0u)
            serial_wdt_feed();
    }
    container_put_le32(header + HDR_CRC, crc ^ 0xFFFFFFFFu);

    total_bytes = FLASH_BACKUP_HEADER_LEN + range_len;
}

uint32_t flash_backup_total(void) {
    return total_bytes;
}

void flash_backup_start(void) {
    offset = 0u;
}

void flash_backup_read(uint8_t *dst, uint32_t len) {
    const volatile uint8_t *src = flash_window(range_addr);

    while (len-- != 0u) {
        if (offset < FLASH_BACKUP_HEADER_LEN)
            *dst++ = header[offset];
        else
            *dst++ = src[offset - FLASH_BACKUP_HEADER_LEN];
        offset++;
    }
}
