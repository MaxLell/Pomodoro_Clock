#ifndef BUTTON_H
#define BUTTON_H

#include "Common.h"

typedef enum
{
    BUTTON_IS_NOT_PRESSED = 0,
    BUTTON_WAS_PRESSED,
    BUTTON_IS_HOLDED_DOWN
} ButtonState_e;

ButtonState_e Button_getState(void);

void Button_ISR(void);

#endif // BUTTON_H
