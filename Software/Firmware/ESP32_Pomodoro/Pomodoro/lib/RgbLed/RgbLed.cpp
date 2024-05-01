/*
 * RgbLed.c
 *
 *  Created on: Nov 29, 2023
 *      Author: maxlell
 */

#include "RgbLed.h"
#include "Common.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip(TOTAL_LEDS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void RgbLed_init(void)
{
  strip.begin();
  strip.clear();
}

void RgbLed_setPixelColor(u8 u8LedIdx,
                          u8 u8Red,
                          u8 u8Green,
                          u8 u8Blue)
{
  { // Input Checks
    ASSERT_MSG(!(u8LedIdx >= TOTAL_LEDS),
               "u8LedIdx out of bounds. Provided Index was %d", u8LedIdx);
  }
  strip.setPixelColor(u8LedIdx, strip.Color(u8Red, u8Green, u8Blue));
}

void RgbLed_show(void)
{
  strip.show();
}

void RgbLed_clear(void)
{
  for (u8 i = 0; i < TOTAL_LEDS; i++)
  {
    RgbLed_setPixelColor(i, 0, 0, 0);
  }
  RgbLed_show();
}
