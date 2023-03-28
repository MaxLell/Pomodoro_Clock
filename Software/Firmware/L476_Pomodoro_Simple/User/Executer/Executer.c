#include "Executer.h"
#include "main.h"
#include "BlinkyLed.h"
#include "StopWatch.h"
#include "Button.h"
#include "RealTimeClock.h"

void Executer_init(void)
{
}
RTC_TimeTypeDef rtcTime = {0};
BOOL Executer_execute(void)
{
    RealTimeClock_Time currentTime = {0};
    currentTime = RealTimeClock_getTime();
    log_info("%d:%d:%d", currentTime.hour, currentTime.minute, currentTime.second);
    log_info("--------------------");
    HAL_Delay(1000);

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