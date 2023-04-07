#include "Executer.h"
#include "main.h"
#include "BlinkyLed.h"
#include "StopWatch.h"
#include "Button.h"
#include "RealTimeClock.h"
#include "LightControl.h"

void Executer_init(void)
{
}

/**
 * @brief  The main execution steps are run in this function.
 */
status_t Executer_execute(void)
{
    // Run the Button module

    // Run the RealTimeClock module

    // Run the PomodoroFSM module

    // Run the LightControl module
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