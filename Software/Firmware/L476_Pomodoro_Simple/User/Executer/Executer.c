#include "Executer.h"
#include "BlinkyLed.h"
#include "StopWatch.h"
#include "Button.h"
#include "RealTimeClock.h"
#include "StopWatch.h"
#include "MessageBroker.h"
#include "Buzzer.h"
#include "LightEffects.h"
#include "PomodoroFsm.h"
#include "RgbLed.h"
#include "Score.h"

void Executer_init(void)
{
    MessageBroker_init();

    StopWatch_init();
    RealTimeClock_init();

    Buzzer_Init();
    LightEffects_init();
    PomodoroFsm_init();
    RgbLed_init();
    Score_init();
}

/**
 * @brief  The main execution steps are run in this function.
 */
status_t Executer_execute(void)
{
    StopWatch_execute();
    RealTimeClock_execute();
    Button_execute();
    Buzzer_execute();
    LightEffects_execute();
    PomodoroFsm_execute();
    RgbLed_execute();
    Score_execute();

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
    // This point must never be reached - if it is, then something is wrong
    // Stop the program.
    assert_true(NULL);
}