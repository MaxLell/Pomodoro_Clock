#include "RgbLed.h"
#include "Arduino.h"

void OnBoardTest_RgbLed_init(void)
{
    RgbLed_init();
}

void OnBoardTest_RgbLed_execute(void)
{
    u32 u32DelayMs = 5;
    for (u8 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 5, 5, 5);
        delay(u32DelayMs);
        RgbLed_show();
    }

    for (u8 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 0, 0, 0);
        delay(u32DelayMs);
        RgbLed_show();
    }
}