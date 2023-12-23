#include "PomodoroControl_StateFunctions.h"

#include "Common.h"
#include "LightEffects.h"

status_e PomodoroControl_StateFn_Idle() { return STATUS_SUCCESS; }

status_e PomodoroControl_StateFn_WorkTime() {
  // remove the corresponding led in accordance to the current Minute

  // only when the sequence is finished, then return Success

  return STATUS_SUCCESS;
}

status_e PomodoroControl_StateFn_Warning() {
  // Fill the ring incrementally up.

  // Only return success when the entire ring is filled up
  return STATUS_SUCCESS;
}

status_e PomodoroControl_StateFn_BreakTime() {
  // Fill the entire ring with very bright light

  // every couple of seconds an Led is switched off

  // when all leds are switched off, then return success
  return STATUS_SUCCESS;
}