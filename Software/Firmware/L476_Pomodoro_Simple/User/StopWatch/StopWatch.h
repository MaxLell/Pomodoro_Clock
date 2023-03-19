#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "Common.h"

void StopWatch_delayMs(uint32_t delay);

BOOL StopWatch_oneSecondPassed(void);

void StopWatch_ISR(void);

#endif // STOPWATCH_H
