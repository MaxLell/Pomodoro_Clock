#include "PomodoroControl_StateFunctions.h"

#include "Common.h"
#include "LightEffects.h"

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_StartingSequence(
    const uint8_t in_u8CurrentMinuteOfTheHour,
    const uint8_t in_u8WorktimePeriodMin,
    const uint8_t in_u8BreaktimePeriodMin) {
  // Create the initial animation - with the Light Effect Animation

  // Render incrementally

  // When finished return Success

  return POMODORO_CONTROL_STATE_FN_STATE__SUCCESS;
}

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_WorkTime(
    const uint8_t in_u8CurrentMinuteOfTheHour) {
  // remove the corresponding led in accordance to the current Minute

  // only when the sequence is finished, then return Success

  return POMODORO_CONTROL_STATE_FN_STATE__SUCCESS;
}

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_Warning() {
  // Fill the ring incrementally up.

  // Only return success when the entire ring is filled up
  return POMODORO_CONTROL_STATE_FN_STATE__SUCCESS;
}

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_BreakTime() {
  // Fill the entire ring with very bright light

  // every couple of seconds an Led is switched off

  // when all leds are switched off, then return success

  return POMODORO_CONTROL_STATE_FN_STATE__SUCCESS;
}