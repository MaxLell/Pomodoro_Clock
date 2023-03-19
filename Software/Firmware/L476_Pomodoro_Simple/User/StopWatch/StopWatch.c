#include "StopWatch.h"

static BOOL oneSecondPassed = FALSE;

void StopWatch_delay(uint32_t delay)
{
    HAL_Delay(delay);
}

BOOL StopWatch_oneSecondPassed(void)
{
    BOOL result = oneSecondPassed;
    oneSecondPassed = FALSE;
    return result;
}

void StopWatch_ISR(void)
{
    oneSecondPassed = TRUE;
}