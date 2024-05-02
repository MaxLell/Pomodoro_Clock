#include "LightEffects_Error.h"
#include "Common.h"
#include "RgbLed.h"
#include "Delay.h"

void LightEffects_DisplayError(void)
{
    for (u32 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 5, 0, 0);
    }
    RgbLed_show();
    Delay_ms(500);
    for (u32 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 0, 0, 0);
    }
    RgbLed_show();
    Delay_ms(500);
}