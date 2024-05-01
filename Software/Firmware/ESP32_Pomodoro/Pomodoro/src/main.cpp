#include <Arduino.h>
#include "RgbLed.h"

#define LED_PIN 13

void setup()
{
  RgbLed_init();
}

void loop()
{
  printf("Hello World\n");
  for (u8 i = 0; i < TOTAL_LEDS; i++)
  {
    RgbLed_setPixelColor(i, 10, 0, 0);
    RgbLed_show();
    delay(10);
  }
  for (u8 i = 0; i < TOTAL_LEDS; i++)
  {
    RgbLed_setPixelColor(i, 0, 0, 0);
    RgbLed_show();
    delay(10);
  }
}