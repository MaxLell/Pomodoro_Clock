#include "Button.h"

#include "Common.h"
#include "stm32l476xx.h"
#include "RegisterAccess.h"

/**
 * The button is connected to PC13
 * on the Nucleo Board
 *
 * Important is: The logic is inverse:
 * Button pressed -> Signal Low
 * Button released -> Signal High
 *
 * The pin is connected to a Pull up resistor.
 */

/**
 * Ressources:
 * https://controllerstech.com/stm32-gpio-input-configuration/
 */

void Button_init()
{
    /* Enable GPIOC Clock*/
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Set the Mode Register to 0 for Pin 13 - Input Mode */
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_0);
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_1);
}

Button_State Button_getState()
{
    Button_State tmp;
    if ((GPIOC->IDR & (1 << 13)))
    {
        tmp = BUTTON_RELEASED;
    }
    else
    {
        tmp = BUTTON_PRESSED;
    }
    return tmp;
}