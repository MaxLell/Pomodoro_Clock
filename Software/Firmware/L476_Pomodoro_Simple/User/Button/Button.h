#ifndef BUTTON_H
#define BUTTON_H

#include "Common.h"

#define BUTTON_PRESSED 0
#define BUTTON_HOLDED_DOWN 1

uint8_t Button_getState(void);

void Button_ISR(void);

#endif // BUTTON_H
