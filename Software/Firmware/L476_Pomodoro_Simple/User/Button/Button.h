#ifndef BUTTON_H
#define BUTTON_H

#include "Common.h"

status_t Button_wasPressed(BOOL *pBButtonWasPressed);

void Button_ISR(void);

void Button_execute(void);

#endif // BUTTON_H
