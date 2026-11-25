#include "app.h"
#include "dmm_remote.h"
#include "protocol.h"
#include "zw_api.h"

void app_mainloop(void) {
    zw_auto_power_off_check();
    dmm_remote_baud_poll();
    protocol_poll();
}
