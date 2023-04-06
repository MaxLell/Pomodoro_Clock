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
RTC_TimeTypeDef rtcTime = {0};

/**
 * @brief  The main execution steps are run in this function.
 */
status_t Executer_execute(void)
{
    /**
     * Get all the inputs
     */
    // Get the current Minute from the RTC
    uint8_t u8Minute = 0;
    RealTimeClock_getCurrentMinute(&u8Minute);

    // Figure out if the button was pressed
    BOOL bButtonPressed = FALSE;
    Button_wasPressed(&bButtonPressed);

    /**
     * Run the sequence
     */

    if (bButtonPressed == TRUE)
    {
        // Start the Light control sequence if it is not already running
        LightControl_execute(u8Minute);

        // OR if the sequence is running, stop it
    }
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