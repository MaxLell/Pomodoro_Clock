#ifndef POMODOROCONTROL_DATATYPES_H
#define POMODOROCONTROL_DATATYPES_H

#include "Common.h"

typedef enum {
  POMODOORO_CONTROL_STATE__IDLE,
  POMODORO_CONTROL_STATE__WORKTIME,
  POMODORO_CONTROL_STATE__WARNING,
  POMODORO_CONTROL_STATE__BREAKTIME,
  POMODORO_CONTROL_STATE__CANCEL_SEQUENCE,
  POMODORO_CONTROL_STATE__INVALID
} PomodoroControl_State_t;

typedef struct {
  // flags
  BOOL bStartPomodoroEventReceived;
  BOOL bTriggerButtonIsPressedContinuously;

  // Current Minute
  uint8_t u8CurrentMinuteOfTheHour;

  // Pomodoro Settings
  uint8_t u8WorktimePeriodMin;
  uint8_t u8BreaktimePeriodMin;

  // State of the State Machine
  PomodoroControl_State_t ePreviousState;
} PomodoroControl_internalStatus_t;

#endif  // POMODOROCONTROL_DATATYPES_H
