#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#include "Common.h"

void Button_Hardware_init();

BOOL Button_Hardware_wasPressed();

void Button_Hardware_Interrupt();

#endif  // BUTTON_HARDWARE_H
