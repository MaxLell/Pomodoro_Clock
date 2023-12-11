#ifndef POMODOROCONTROL_STATEFUNCTIONS_H
#define POMODOROCONTROL_STATEFUNCTIONS_H

#include "PomodoroControl_Datatypes.h"

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_StartingSequence();

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_WorkTime();

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_Warning();

PomodoroControl_StateFn_status_t PomodoroControl_StateFn_BreakTime();

#endif  // POMODOROCONTROL_STATEFUNCTIONS_H
