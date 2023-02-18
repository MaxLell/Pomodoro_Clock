#include "GPIO.h"
#include "stm32l476xx.h"
#include "Common.h"

void GPIO_PushButtonPC13_init()
{
    /* Enable GPIOC Clock*/
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Set the Mode Register to 0 for Pin 13 - Input Mode */
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_0);
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_1);
}

void GPIO_BlinkyLedPA5_init()
{
    /* Turn on the Clock for GPIOA */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Set PA5 to output Mode */
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
}

void GPIO_BlinkyLedPA5_enable()
{
    /* set HIGH value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BS_5;
}

void GPIO_BlinkyLedPA5_disable(void)
{
    /* set LOW value on pin PA5 */
    GPIOA->BSRR |= GPIO_BSRR_BR_5;
}

void GPIO_BlinkyLedPA5_toggle(void)
{
    /**
     * This reads in the 5th register of PortA -> PA5
     * This is the same pin, to which the LED is attached
     * to
     */
    if ((GPIOA->IDR & (1 << 5)))
    {
        /**
         * When the LED was on: Switch it off.
         */
        GPIO_BlinkyLedPA5_disable();
    }
    else
    {
        /**
         * When the LED was off: Switch it on.
         */
        /**
         * Setting the LED, changes the value that is read
         * on the Input Data Register
         */
        GPIO_BlinkyLedPA5_enable();
    }
}