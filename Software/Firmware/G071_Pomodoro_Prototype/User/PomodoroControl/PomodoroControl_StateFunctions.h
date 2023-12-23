#ifndef POMODOROCONTROL_STATEFUNCTIONS_H
#define POMODOROCONTROL_STATEFUNCTIONS_H

#include "Common.h"
#include "PomodoroControl_Datatypes.h"

status_e PomodoroControl_StateFn_WorkTime();

status_e PomodoroControl_StateFn_Warning();

status_e PomodoroControl_StateFn_BreakTime();

status_e PomodoroControl_StateFn_CancelSequence();

#endif  // POMODOROCONTROL_STATEFUNCTIONS_H
