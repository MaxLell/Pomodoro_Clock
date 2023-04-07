#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "Common.h"

void StopWatch_delayMs(uint32_t delay);

status_t StopWatch_oneSecondPassed(BOOL *bOneSecondPassed);

void StopWatch_ISR(void);

void StopWatch_init(void);

void StopWatch_execute(void);

#endif // STOPWATCH_H
