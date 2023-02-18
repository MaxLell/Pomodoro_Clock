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