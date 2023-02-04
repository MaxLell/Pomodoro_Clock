#include "Main.h"
#include "Common.h"
#include "Rcc.h"
#include "stm32l4xx.h"

/* delay counter */
#define DELAY_MAX 50000

#ifdef TEST
int TestableMain(void)
#else
int main(void)
#endif
{
    printf("huhu\n");

    /* Turn on the Clock for GPIOA */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Set PA5 to output Mode */
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    while (TRUE)
    {
        /* set HIGH value on pin PA5 */
        GPIOA->BSRR |= GPIO_BSRR_BS_5;
        for (uint32_t i = DELAY_MAX; i--;)
            ;

        /* set LOW value on pin PA5 */
        GPIOA->BSRR |= GPIO_BSRR_BR_5;
        for (uint32_t i = DELAY_MAX; i--;)
            ;
    }
}
