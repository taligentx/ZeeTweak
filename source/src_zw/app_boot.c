#include <stdint.h>

extern uint32_t __app_data_init;
extern uint32_t __app_data_start;
extern uint32_t __app_bss_start;
extern uint32_t __app_bss_end;

extern void zw_main(void);
extern void app_init(void);


int main(void)
{
    volatile uint32_t *dst = (volatile uint32_t *)&__app_data_start;
    volatile uint32_t *src = (volatile uint32_t *)&__app_data_init;
    uint32_t nwords = ((uint32_t)&__app_bss_start -
                       (uint32_t)&__app_data_start) / 4u;
    for (uint32_t i = 0; i < nwords; i++)
        dst[i] = src[i];

    volatile uint32_t *b = (volatile uint32_t *)&__app_bss_start;
    volatile uint32_t *e = (volatile uint32_t *)&__app_bss_end;
    for (; b < e; b++)
        *b = 0u;

    app_init();
    zw_main();
    for (;;)
        ;
}
