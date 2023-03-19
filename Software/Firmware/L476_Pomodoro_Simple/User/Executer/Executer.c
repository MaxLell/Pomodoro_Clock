#include "Executer.h"
#include "main.h"
#include "BlinkyLed.h"
#include "StopWatch.h"
#include "Button.h"

void Executer_init(void)
{
}

BOOL Executer_execute(void)
{
    ButtonState_e buttonState = Button_getState();
    if (buttonState == BUTTON_WAS_PRESSED)
    {
        BlinkyLed_toggle();
        StopWatch_delayMs(100);
    }
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