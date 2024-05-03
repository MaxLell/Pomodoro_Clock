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

static bool bIsInitialized = false;

void RgbLed_init(void)
{
  ASSERT_MSG(false == bIsInitialized, "RgbLed already initialized");
  strip.begin();
  strip.clear();
  bIsInitialized = true;
}

void RgbLed_setPixelColor(u8 u8LedIdx,
                          u8 u8Red,
                          u8 u8Green,
                          u8 u8Blue)
{
  { // Input Checks
    ASSERT_MSG(!(u8LedIdx >= TOTAL_LEDS),
               "u8LedIdx out of bounds. Provided Index was %d", u8LedIdx);
    ASSERT_MSG(true == bIsInitialized, "RgbLed not initialized");
  }
  strip.setPixelColor(u8LedIdx, strip.Color(u8Red, u8Green, u8Blue));
}

void RgbLed_show(void)
{
  ASSERT_MSG(true == bIsInitialized, "RgbLed not initialized");
  strip.show();
}

void RgbLed_clear(void)
{
  ASSERT_MSG(true == bIsInitialized, "RgbLed not initialized");
  for (u8 i = 0; i < TOTAL_LEDS; i++)
  {
    RgbLed_setPixelColor(i, 0, 0, 0);
  }
  RgbLed_show();
}
