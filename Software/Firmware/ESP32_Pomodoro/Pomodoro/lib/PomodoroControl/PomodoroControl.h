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
    uint16_t u16DurationPerIncrementMsec;
    u8 u8FillingMin;
    int8_t i8Animation;
    BOOL bIsComplete;
    BOOL bIsTimerInitialized;
} PCTRL_RingCountdown_t;

void PomodoroControl_init(void);

status_e PomodoroControl_execute(void);

#endif // POMODOROCONTROL_H
