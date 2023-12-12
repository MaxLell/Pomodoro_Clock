#ifndef POMODOROCONTROL_DATATYPES_H
#define POMODOROCONTROL_DATATYPES_H

#include "Common.h"

typedef enum {
  POMDOORO_CONTROL_STATE__IDLE,
  POMODORO_CONTROL_STATE__STARTING_SEQUENCE,
  POMODORO_CONTROL_STATE__WORKTIME,
  POMODORO_CONTROL_STATE__WARNING,
  POMODORO_CONTROL_STATE__BREAKTIME,
  POMODORO_CONTROL_STATE__CANCEL_SEQUENCE,
  POMODORO_CONTROL_STATE__INVALID
} PomodoroControl_State_t;

typedef enum {
  POMODORO_CONTROL_STATE_FN_STATE__PENDING,
  POMODORO_CONTROL_STATE_FN_STATE__SUCCESS,
  POMODORO_CONTROL_STATE_FN_STATE__ERROR
} PomodoroControl_StateFn_status_t;

typedef struct {
  // flags
  BOOL bStartPomodoroEventReceived;
  BOOL bTriggerButtonIsPressedContinuously;
  BOOL bTriggerButtonIsReleased;

  // Current Minute
  uint8_t u8CurrentMinuteOfTheHour;

  // Pomodoro Settings
  uint8_t u8WorktimePeriodMin;
  uint8_t u8BreaktimePeriodMin;
} PomodoroControl_internalStatus_t;

#endif  // POMODOROCONTROL_DATATYPES_H
