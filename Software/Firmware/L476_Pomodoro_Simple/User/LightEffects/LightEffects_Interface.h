#ifndef LIGHTEFFECTS_INTERFACE_H
#define LIGHTEFFECTS_INTERFACE_H

#include "Common.h"

typedef enum LightEffect_LedConfig_e
{
    LIGHTEFFECTS_LED_OFF = 1U,

    LIGHTEFFECTS_LED_RED_LOW = 5U,
    LIGHTEFFECTS_LED_RED_MID = 6U,
    LIGHTEFFECTS_LED_RED_HIGH = 7U,

    LIGHTEFFECTS_LED_GREEN_LOW = 9U,
    LIGHTEFFECTS_LED_GREEN_MID = 10U,
    LIGHTEFFECTS_LED_GREEN_HIGH = 11U,

    LIGHTEFFECTS_LED_BLUE_LOW = 13U,
    LIGHTEFFECTS_LED_BLUE_MID = 14U,
    LIGHTEFFECTS_LED_BLUE_HIGH = 15U,
} LightEffect_LedConfig;

#endif // LIGHTEFFECTS_INTERFACE_H