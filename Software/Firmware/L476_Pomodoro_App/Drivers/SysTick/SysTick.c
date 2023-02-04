#include "SysTick.h"

#include "stm32l476xx.h"
#include "RegisterAccess.h"

/**
 * Ressources
 * https://www.keil.com/pack/doc/CMSIS/Core/html/group__SysTick__gr.html
 * https://github.com/LonelyWolf/stm32/blob/master/SSD1306/delay.c
 * https://klinikarduino.github.io/stm32f103_spl/part_4/index.html
 */

#define SYSTEM_CLOCK_SPEED 16000000
__IO STATIC uint32_t msTicks = 0;

void SysTick_init(void)
{
    /* Triggers the SysTick Handler every ms */
    SysTick_Config(SYSTEM_CLOCK_SPEED / 1000);
}
void delay_ms(uint32_t ms)
{
    /* Enable the SysTick timer */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    msTicks = 0;
    while (msTicks < ms)
    {
        /* Wait like the sitting duck that you are! */
    }

    /* Disable the SysTick timer */
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
    /* SysTick interrupt Handler. */
    msTicks++;
}