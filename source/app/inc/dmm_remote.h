// Sends DMM data as FS9922-style frames

#ifndef DMM_REMOTE_H
#define DMM_REMOTE_H

#include <stdint.h>

uint32_t dmm_remote_flush(uint32_t *timer);
void dmm_remote_baud_poll(void);

#endif
