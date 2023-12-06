#include "LightEffects.h"

#include "CountdownTimer.h"
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
  static timer_t sTimer;
  static uint8_t u8CurrentLedIndex = 0;
  const uint8_t brightness = 30;

  timer_status_t sTimerStatus = Countdown_getTimerStatus(&sTimer);
  if (TIMER_NOT_ENABLED == sTimerStatus) {
    // First execution
    // Set the timer
    Countdown_initTimer(&sTimer, u16PeriodPerIncrementMs, CONTINOUS_MODE);
    Countdown_startTimer(&sTimer);

    // Set the first LED
    RgbLed_setPixelColor(u8CurrentLedIndex, brightness, brightness, brightness);
  }

  if (TIMER_EXPIRED == sTimerStatus) {
    // Disable the current running LED
    RgbLed_setPixelColor(u8CurrentLedIndex, 0, 0, 0);

    // Increment the ledIndex
    u8CurrentLedIndex++;

    if (u8CurrentLedIndex >= RGB_LED_TOTAL_LEDS) {
      // Stop the timer
      Countdown_stopTimer(&sTimer);

      // Set the sequence status to complete
      *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_COMPLETE;
    } else {
      // Set the next LED
      RgbLed_setPixelColor(u8CurrentLedIndex, brightness, brightness,
                           brightness);
      *out_eSequenceStatus = E_LIGHT_EFFECTS_STATUS_SEQUENCE_IN_PROGRESS;
    }
  }
}