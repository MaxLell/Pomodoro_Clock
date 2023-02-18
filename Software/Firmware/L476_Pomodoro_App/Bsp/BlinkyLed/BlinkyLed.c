#include "BlinkyLed.h"

#include "Common.h"
#include "stm32l476xx.h"

#include "GPIO.h"

/**
 * The LED blinky LED is connected to PA5
 */

void BlinkyLed_init(void)
{
    GPIO_BlinkyLedPA5_init();
}

void BlinkyLed_enable(void)
{
    GPIO_BlinkyLedPA5_enable();
}

void BlinkyLed_disable(void)
{
    GPIO_BlinkyLedPA5_disable();
}

void BlinkyLed_toggle(void)
{
    GPIO_BlinkyLedPA5_toggle();
}