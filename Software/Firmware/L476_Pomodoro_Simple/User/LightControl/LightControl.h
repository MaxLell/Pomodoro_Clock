#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include "Common.h"
#include "Config.h"

#define MINUTES_IN_HOUR 60

typedef enum
{
    LIGHTCONTROL_LED_OFF = 1U,
    LIGHTCONTROL_LED_RED = 5U,
    LIGHTCONTROL_LED_GREEN = 7U,
    LIGHTCONTROL_LED_BLUE = 9U,
} LightControl_Colors;

status_t LightControl_execute();

void LightControl_init();

#endif // LIGHTCONTROL_H
