
#include "OnBoardTest_CountdownTimer.h"
#include "Common.h"
#include "CountdownTimer.h"
#include "BlinkyLed.h"
#include "Delay.h"

static CountdownTimer_t sTimer;

void OnBoardTest_CountdownTimer_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                Countdown and BlinkyLed Test");
    printf("%s\n", "************************************************************");

    // initialize the BlinkyLed
    BlinkyLed_init();

    // Initialize the timer
    Countdown_initTimerMs(&sTimer, 100, E_OPERATIONAL_MODE_CONTIUNOUS);

    // Start the Timer
    Countdown_resetAndStartTimer(&sTimer);
}

void OnBoardTest_CountdownTimer_execute(void)
{
    // Check if the timer has expired
    if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sTimer))
    {
        // Toggle the LED
        BlinkyLed_toggle();
    }
    else
    {
        Delay_ms(1);
    }
}