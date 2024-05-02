#ifndef POMODOROCONTROL_H
#define POMODOROCONTROL_H

#include "Common.h"
#include "PomodoroControl_Datatypes.h"

typedef struct
{
    u8 u8Worktime;
    u8 u8Breaktime;
    u8 au8MinuteArray[TOTAL_MINUTES];
} PCTRL_Progress_t;

typedef struct
{
    u16 u16DurationPerIncrementMsec;
    u8 u8FillingMin;
    s8 i8Animation;
    bool bIsComplete;
    bool bIsTimerInitialized;
} PCTRL_RingCountdown_t;

void PomodoroControl_init(void);

status_e PomodoroControl_execute(void);

#endif // POMODOROCONTROL_H
