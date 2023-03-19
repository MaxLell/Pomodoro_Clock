#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "Common.h"

void StopWatch_delay(uint32_t delay);

BOOL StopWatch_timeInSecondsPassed(uint32_t timeInSeconds);

void StopWatch_ISR(void);

#endif // STOPWATCH_H
