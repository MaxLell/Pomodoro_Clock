#include "Executer.h"
#include "main.h"
#include "BlinkyLed.h"
#include "StopWatch.h"

void Executer_init(void)
{
}

BOOL Executer_execute(void)
{
    BlinkyLed_Toggle();
    StopWatch_delayMs(1000);
    log_info("Hello World!");
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