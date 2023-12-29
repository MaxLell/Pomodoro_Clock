#include "LightEffects.h"

#include "CountdownTimer.h"
#include "Delay.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"
#include "math.h"

/************************************************************
 * Function Prototypes
 ************************************************************/

STATIC void LightEffects_updateMinuteToLedArray(
    uint8_t in_u8OffsetMin,
    uint8_t* inout_au8MinuteToLedConfigArray);

/************************************************************
 * Implementation
 ************************************************************/

void LightEffects_scaleArray(const uint8_t* const in_au8SourceArray,
                             uint8_t in_u8SourceArraySize,
                             uint8_t* out_au8TargetArray,
                             uint8_t in_u8TargetArraySize) {
  {  // Input Checks
    ASSERT_MSG(!(in_au8SourceArray == NULL), "in_au8SourceArray is NULL Ptr");
    ASSERT_MSG(!(out_au8TargetArray == NULL), "in_au8SourceArray is NULL Ptr");
    ASSERT_MSG(!(in_u8SourceArraySize == 0),
               "Provided in_u8SourceArraySize needs to be larger then 0");
    ASSERT_MSG(!(in_u8TargetArraySize == 0),
               "Provided in_u8TargetArraySize needs to be larger then 0");
  }

  // Calculate the Scale Factor
  float fScaleFactor =
      (float)in_u8SourceArraySize / (float)in_u8TargetArraySize;
  // Scale the Array
  for (uint8_t i = 0; i < in_u8TargetArraySize; i++) {
    out_au8TargetArray[i] = in_au8SourceArray[(uint8_t)(i * fScaleFactor)];
  }
}

/*
 ######### New Implementation #########
*/

void LightEffects_DotAroundTheCircle(status_e* out_eSequenceStatus,
                                     uint16_t u16PeriodPerIncrementMs) {
  {
    // Input Checks
    ASSERT_MSG(!(NULL == out_eSequenceStatus),
               "Sequence Status cannot be NULL");
    ASSERT_MSG(!(u16PeriodPerIncrementMs == 0U), "Period cannot be 0");
  }
  // Variable Declarations
  static uint8_t u8LedIndex = 0;
  uint8_t effect[RGB_LED_TOTAL_LEDS] = {2, 5, 5, 5, 2};
  uint8_t effect_size = sizeof(effect);

  // Increment the ledIndex
  u8LedIndex++;

  if (u8LedIndex == RGB_LED_TOTAL_LEDS) {
    // Set the sequence status to complete
    *out_eSequenceStatus = STATUS_PENDING;

    // Reset the ledIndex
    u8LedIndex = 0;

    // Disable all LEDs
    RgbLed_clear();
  } else {
    for (uint8_t i = 0; i < RGB_LED_TOTAL_LEDS; i++) {
      RgbLed_setPixelColor(i, 0, 0, 0);
    }

    for (uint8_t i = 0; i < effect_size; i++) {
      uint8_t tmp = (u8LedIndex + i) % RGB_LED_TOTAL_LEDS;
      RgbLed_setPixelColor(tmp, effect[i], effect[i], effect[i]);
    }

    // Set the Sequence Status to in progress
    *out_eSequenceStatus = STATUS_PENDING;
  }
  // Wait a fixed delay
  Delay_ms(u16PeriodPerIncrementMs);

  // Show the sequence on the LEDs
  RgbLed_show();
}

void LightEffects_ClearAllRingLeds(void) {
  RgbLed_clear();
  Delay_ms(10);
  RgbLed_show();
}
