#include "Main.h"
#include "Common.h"
#include "Rcc.h"
#include "stm32l4xx.h"

/* delay counter */

void simple_delay()
{
    __IO uint16_t max_delay = 50000;
    for (uint32_t i = max_delay; i--;)
        ;
}

__IO uint32_t msTicks;

/**
 * Ressources
 * https://www.keil.com/pack/doc/CMSIS/Core/html/group__SysTick__gr.html
 * https://github.com/LonelyWolf/stm32/blob/master/SSD1306/delay.c
 * https://klinikarduino.github.io/stm32f103_spl/part_4/index.html
 */

void SysTick_Handler(void)
{
    /* SysTick interrupt Handler. */
    msTicks++;
}

void delay_ms(uint32_t ms)
{
    msTicks = 0;
    while (msTicks < ms)
    {
        /* Wait like the sitting duck that you are! */
    }
}

#ifdef TEST
int TestableMain(void)
#else
int main(void)
#endif
{
    printf("huhu\n");

    Rcc_Init();

    /* Triggers the SysTick Handler every ms */
    SysTick_Config(16000000 / 1000);

    /* Turn on the Clock for GPIOA */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Set PA5 to output Mode */
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    while (TRUE)
    {
        /* set HIGH value on pin PA5 */
        GPIOA->BSRR |= GPIO_BSRR_BS_5;
        delay_ms(100);

        /* set LOW value on pin PA5 */
        GPIOA->BSRR |= GPIO_BSRR_BR_5;
        delay_ms(100);
    }
}
