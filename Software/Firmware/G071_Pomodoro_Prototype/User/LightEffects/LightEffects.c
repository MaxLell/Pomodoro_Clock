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
  static uint8_t u8CurrentLedIndex = 0;
  const uint8_t u8Brightness = 30;

  // Disable the current running LED
  RgbLed_setPixelColor(u8CurrentLedIndex, 0, 0, 0);

  // Increment the ledIndex
  u8CurrentLedIndex++;

  if (u8CurrentLedIndex >= RGB_LED_TOTAL_LEDS) {
    // Set the sequence status to complete
    *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE;

    // Reset the ledIndex
    u8CurrentLedIndex = 0;

    // Disable all LEDs
    RgbLed_clear();
  } else {
    // Set the next LED
    RgbLed_setPixelColor(u8CurrentLedIndex, u8Brightness, u8Brightness,
                         u8Brightness);

    // Set the Sequence Status to in progress
    *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_IN_PROGRESS;
  }
  // Wait a fixed delay
  Delay_ms(u16PeriodPerIncrementMs);

  // Show the sequence on the LEDs
  RgbLed_show();
}