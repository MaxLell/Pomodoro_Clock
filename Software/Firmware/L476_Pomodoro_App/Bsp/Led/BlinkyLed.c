#include "BlinkyLed.h"

#include "stm32l476xx.h"
#include "RegisterAccess.h"

void BlinkyLed_init(void)
{
    /* Turn on the Clock for GPIOA */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Set PA5 to output Mode */
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
}
void BlinkyLed_enable(void)
{
    /* set HIGH value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BS_5;
}
void BlinkyLed_disable(void)
{
    /* set LOW value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BR_5;
}