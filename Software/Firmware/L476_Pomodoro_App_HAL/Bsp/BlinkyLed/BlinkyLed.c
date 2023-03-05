#include "BlinkyLed.h"

#include "Common.h"
#include "main.h"
/**
 * The LED blinky LED is connected to PA5
 */

void BlinkyLed_init(void) { /* You do nuthin John Snow!! */
}

void BlinkyLed_enable(void) { /* You do nuthin John Snow!! */
}

void BlinkyLed_disable(void) { /* You do nuthin John Snow!! */
}

void BlinkyLed_toggle(void) { HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); }
