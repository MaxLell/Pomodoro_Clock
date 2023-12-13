#ifndef REALTIMECLOCK_HARDWARE_H
#define REALTIMECLOCK_HARDWARE_H
#include "Common.h"
#include "RealTimeClock.h"
#include "RealtimeClock_Datatypes.h"

status_t RealTimeClockHW_getTimeAndDate(TimeAndDate_t *in_pTimeAndDate);

#endif  // REALTIMECLOCK_HARDWARE_H
