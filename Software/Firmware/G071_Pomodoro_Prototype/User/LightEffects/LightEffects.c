#include "LightEffects.h"

#include "CountdownTimer.h"
#include "Delay.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"

void LightEffects_DotAroundTheCircle(
    LightEffects_SequenceStatus_e* out_eSequenceStatus,
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
    *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE;

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
    *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_IN_PROGRESS;
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