// Firmware prototypes

#ifndef ZW_API_H
#define ZW_API_H

#include <stdint.h>

void zw_main(void); // Vendor entry point (stock main)
uint32_t HAL_GetTick(void);
void HAL_Delay(uint32_t ms);
uint32_t zw_timer_check(uint32_t *timer);
void zw_delay_cycles_small_hw(uint32_t cycles);
void zw_delay_cycles_large_hw(uint32_t cycles);
void zw_fpga_all_reset(void);
void zw_fpga_acq_stop(void);
void zw_fpga_acq_reset(void);
uint32_t check_power_button_status(void);
void zw_power_on(int seconds);
void zw_auto_power_off_check(void);

typedef struct {
    volatile uint32_t *Instance;
    uint32_t Init_Reload;
} zw_wdg_handle_t;

extern zw_wdg_handle_t hwdg;

uint32_t zw_draw_string_small(const uint8_t *str, uint32_t x, int32_t y, uint32_t len, uint8_t fg, int16_t bg);
uint32_t zw_draw_string_large(const uint8_t *str, uint32_t x, int32_t y, uint32_t len, uint8_t fg, int16_t bg);
void zw_draw_bitmap(const uint16_t *image, uint16_t x, uint16_t y, uint32_t width, uint32_t height);

extern uint8_t framebuffer[320 * 240];
extern uint16_t scope_palette_RAM[256];
extern uint8_t global_settings[];
extern const volatile uint8_t scope_render_record_ch1[];
extern const volatile uint8_t scope_render_record_ch2[];
extern const volatile uint8_t scope_display_rebuild_counter;
extern const uint8_t scope_acq_destination_ch1[];
extern const uint8_t scope_acq_destination_ch2[];
extern const uint8_t scope_measurement_array_ch1[];
extern const uint8_t scope_measurement_array_ch2[];
extern const volatile uint8_t dmm_rx_buffer[];
extern const volatile int32_t dmm_measurement_value;
extern const volatile uint8_t dmm_mode_index;
extern const volatile uint8_t dmm_digit_0, dmm_digit_1;
extern const volatile uint8_t dmm_digit_2, dmm_digit_3;
extern const volatile uint8_t dmm_dp_0[];
extern volatile uint8_t keypress_with_short_long_flag;
void zw_scope_fetch_samples_generic(int32_t offset, uint32_t count);

#endif
