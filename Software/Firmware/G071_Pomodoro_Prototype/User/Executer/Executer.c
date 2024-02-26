#include "Executer.h"

#include "Button.h"
#include "MessageBroker.h"
#include "OnBoardTest.h"
#include "RealTimeClock.h"

STATIC BOOL bAreOnboardTestsRunning = FALSE;

/**
 * @brief  This function initializes the modules used in the program.
 */
void Executer_init(void)
{
    bAreOnboardTestsRunning = OnBoardTest_isRunning();
    if (bAreOnboardTestsRunning == TRUE)
    {
        OnBoardTest_init();
    }
    else
    {
        MessageBroker_init();
        // Add in the modules here
    }
}

/**
 * @brief  The main execution steps are run in this function.
 */
status_e Executer_execute(void)
{
    if (bAreOnboardTestsRunning == TRUE)
    {
        OnBoardTest_execute();
    }
    else
    {
        // Add in the modules here
    }
    return STATUS_OK;
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
    while (Executer_execute() == STATUS_OK)
    {
        /**
         * The main execution steps are run in the Executer_execute() function.
         */
    }
    ASSERT_MSG(NULL, "shall never reached");
}