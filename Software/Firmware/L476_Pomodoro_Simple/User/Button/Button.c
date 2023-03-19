#include "Button.h"

static ButtonState_e buttonState = BUTTON_IS_NOT_PRESSED;

ButtonState_e Button_getState(void)
{
    return buttonState;
}

void Button_ISR(void)
{
    buttonState = BUTTON_WAS_PRESSED;
}