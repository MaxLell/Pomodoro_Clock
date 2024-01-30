#ifndef POMODOROCONTROL_HELPER_H
#define POMODOROCONTROL_HELPER_H

#include "Common.h"
#define MAX_NOF_POMODORO_MINUTES 120

typedef struct
{
    uint8_t u8Worktime;
    uint8_t u8Breaktime;
    uint8_t au8MinuteArray[MAX_NOF_POMODORO_MINUTES];
} PomodoroControl_helper;

void PomodoroControl_helper_getMinuteArray(PomodoroControl_helper *const inout_sSelf);

#endif // POMODOROCONTROL_HELPER_H
