#include "Button.h"

static BOOL bButtonState = FALSE;

status_t Button_wasPressed(BOOL *pBButtonWasPressed)
{
    *pBButtonWasPressed = bButtonState;

    // Reset the button state after reading it
    bButtonState = FALSE;
    return STATUS_OK;
}

void Button_ISR(void)
{
    bButtonState = TRUE;
}