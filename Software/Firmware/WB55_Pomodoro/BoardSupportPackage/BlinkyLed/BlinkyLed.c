#include "BlinkyLed.h"

#include "Common.h"
#include "main.h"
/**
 * The LED blinky LED is connected to PA5
 */

void BlinkyLed_init(void)
{ /* You do nuthin John Snow!! */
}

void BlinkyLed_enable(void)
{ /* You do nuthin John Snow!! */
}

void BlinkyLed_disable(void)
{ /* You do nuthin John Snow!! */
}

void BlinkyLed_toggle(void)
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    return;
}
