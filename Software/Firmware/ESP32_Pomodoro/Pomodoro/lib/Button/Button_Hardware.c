#include "Button_Datatypes.h"
#include "Button_Hardware.h"
#include "Arduino.h"
#include "Common.h"

void BtnHw_init(void)
{
    pinMode(TRIGGER_BTN_Pin, INPUT_PULLUP);
}

bool BtnHw_getState(const ButtonTypes_e in_eButton)
{
    // Input argument checks
    ASSERT_MSG(!(in_eButton >= E_BTN_LAST), "in_eButton is invalid");
    ASSERT_MSG(!(in_eButton <= E_BTN_INVALID), "in_eButton is invalid");

    switch (in_eButton)
    {
    case E_BTN_TRIGGER:
        return digitalRead(TRIGGER_BTN_Pin);
        break;
    default:
        ASSERT_MSG(false, "in_eButton is invalid");
        return false;
    }
}
