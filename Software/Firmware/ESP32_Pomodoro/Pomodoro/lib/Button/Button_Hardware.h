#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#include "Common.h"
#include "Button_Datatypes.h"

#define TRIGGER_BTN_Pin 14

void BtnHw_init(void);

bool BtnHw_getState(const ButtonTypes_e in_eButton);

#endif // BUTTON_HARDWARE_H
