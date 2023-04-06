#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

#include "Common.h"

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} RealTimeClock_Time;

RealTimeClock_Time RealTimeClock_getTime(void);

status_t RealTimeClock_getCurrentMinute(uint8_t *u8Minute);

#endif // REALTIMECLOCK_H
