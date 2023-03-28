#include "Executer.h"
#include "main.h"
#include "BlinkyLed.h"
#include "StopWatch.h"
#include "Button.h"
#include "RealTimeClock.h"

extern RTC_HandleTypeDef hrtc;

void Executer_init(void)
{
}
RTC_TimeTypeDef rtcTime = {0};
BOOL Executer_execute(void)
{

    return EXECUTER_OK;
}

void Executer_run(void)
{
    Executer_init();
    while (Executer_execute() == EXECUTER_OK)
    {
        /**
         * The main execution steps are run in the Executer_execute() function.
         */
    }
}