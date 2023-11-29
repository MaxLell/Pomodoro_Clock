#include "BlinkyLed.h"
#include "main.h"

void BlinkyLed_toggle(void)
{
    HAL_GPIO_TogglePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin);
}

void BlinkLed_enable(void)
{
    HAL_GPIO_WritePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin, GPIO_PIN_SET);
}

void BlinkLed_disable(void)
{
    HAL_GPIO_WritePin(BLINKY_LED_GPIO_Port, BLINKY_LED_Pin, GPIO_PIN_RESET);
}