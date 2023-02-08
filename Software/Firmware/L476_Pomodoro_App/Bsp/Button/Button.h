#ifndef BUTTON_H
#define BUTTON_H

#include "Common.h"

typedef enum
{
    BUTTON_PRESSED = 0U,
    BUTTON_RELEASED
} Button_State;

void Button_init();

Button_State Button_getState();

BOOL Button_wasPressed();

#endif // BUTTON_H
