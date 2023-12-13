#ifndef POMODOROCONTROL_STATEFUNCTIONS_H
#define POMODOROCONTROL_STATEFUNCTIONS_H

#include "PomodoroControl_Datatypes.h"

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_StartingSequence(
    const uint8_t in_u8CurrentMinuteOfTheHour,
    const uint8_t in_u8WorktimePeriodMin,
    const uint8_t in_u8BreaktimePeriodMin);

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_WorkTime(
    const uint8_t in_u8CurrentMinuteOfTheHour);

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_Warning();

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_BreakTime();

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_CancelSequence();

#endif  // POMODOROCONTROL_STATEFUNCTIONS_H
