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

/**
 * @brief  The main execution steps are run in this function.
 */
BOOL Executer_execute(void)
{
    RealTimeClock_Time currentTime = {0};
    currentTime = RealTimeClock_getTime();
    log_info("%d:%d:%d", currentTime.hour, currentTime.minute, currentTime.second);
    log_info("--------------------");
    HAL_Delay(1000);

    return EXECUTER_OK;
}

/**
 * This function is called from the main() function in main.c.
 * It is the main execution loop of the program.
 * The reason why the execution is built like this, is because
 * with this way a unit test framework run the main execution task
 * one step at a time. This is useful for debugging and testing.
 */
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