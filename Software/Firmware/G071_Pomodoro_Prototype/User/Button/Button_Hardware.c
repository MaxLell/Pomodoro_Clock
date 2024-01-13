#include "Button_Hardware.h"
#include "main.h"

BOOL Button_getState()
{
    GPIO_PinState bState = HAL_GPIO_ReadPin(TRIGGER_BTN_GPIO_Port, TRIGGER_BTN_Pin);
    return (bState == GPIO_PIN_SET) ? TRUE : FALSE;
}