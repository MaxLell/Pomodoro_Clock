#include "RgbLed.h"
#include "Arduino.h"
#include "Delay.h"

void OnBoardTest_RgbLed_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        RgbLed Test");
    printf("%s\n", "************************************************************");

    RgbLed_init();
}

void OnBoardTest_RgbLed_execute(void)
{
    u32 u32DelayMs = 5;
    for (u8 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 5, 5, 5);
        Delay_ms(u32DelayMs);
        RgbLed_show();
    }

    for (u8 i = 0; i < TOTAL_LEDS; i++)
    {
        RgbLed_setPixelColor(i, 0, 0, 0);
        Delay_ms(u32DelayMs);
        RgbLed_show();
    }
}