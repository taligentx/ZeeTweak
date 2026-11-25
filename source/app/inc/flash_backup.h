// Persistent flash data backup (UUID, calibration, settings, screenshots)

#ifndef FLASH_BACKUP_H
#define FLASH_BACKUP_H

#include <stdint.h>

#define FLASH_BACKUP_BASE       0x08096000u
#define FLASH_BACKUP_LIMIT      0x080FF000u
#define FLASH_BACKUP_FLASH_BASE 0x08000000u
#define FLASH_BACKUP_FLASH_SIZE 0x00100000u
#define FLASH_BACKUP_VERSION    1u
#define FLASH_BACKUP_HEADER_LEN 32u

uint32_t flash_backup_range(uint32_t addr, uint32_t len);
void flash_backup_prepare(void);
uint32_t flash_backup_total(void);
void flash_backup_start(void);
void flash_backup_read(uint8_t *dst, uint32_t len);

#endif
