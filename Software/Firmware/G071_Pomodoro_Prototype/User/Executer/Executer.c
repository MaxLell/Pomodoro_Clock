#include "Executer.h"

#include "Button.h"
#include "MessageBroker.h"
#include "OnBoardTest.h"
#include "RealTimeClock.h"
#include "ContextManagement.h"
#include "SeekingAttention.h"
#include "PomodoroControl.h"
#include "CfgStore.h"
#include "Score.h"
#include "Settings.h"
#include "Encoder.h"
#include "WatchDog.h"

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
        printf("%s\n", "############################################################");
        printf("%s\n", "--                 Nominal Behaviour                      --");
        printf("%s\n", "############################################################");

        MessageBroker_init();
        Button_init();
        ContextManagement_init();
        SeekingAttention_init();
        PomodoroControl_init();
        Score_init();
        CfgStore_init();
        Settings_init();
        Encoder_init();

        // Feed the Watchdog
        Watchdog_Feed();

        log_info("Init Complete");
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
        Button_execute();
        ContextManagement_execute();
        SeekingAttention_execute();
        PomodoroControl_execute();
        Score_execute();
        CfgStore_execute();
        Encoder_execute();
        Settings_execute();

        // Feed the Watchdog
        Watchdog_Feed();
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