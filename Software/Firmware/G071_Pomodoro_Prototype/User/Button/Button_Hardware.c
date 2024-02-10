#include "Button_Datatypes.h"
#include "Button_Hardware.h"
#include "main.h"

STATIC BOOL Button_getHardwareState( GPIO_TypeDef*   in_psGpioPort,  uint16_t in_u16Pin){
    
    GPIO_PinState bState = HAL_GPIO_ReadPin(in_psGpioPort, in_u16Pin);
    return (bState == GPIO_PIN_SET) ? TRUE : FALSE;
}

BOOL Button_getState(const ButtonTypes_e in_eButton){
    // Input argument checks
    ASSERT_MSG(!(in_eButton >= E_BUTTON_LAST), "in_eButton is invalid");
    ASSERT_MSG(!(in_eButton <= E_BUTTON_INVALID), "in_eButton is invalid");

    switch (in_eButton)
    {
        case E_BUTTON_TRIGGER:
            return Button_getHardwareState(TRIGGER_BTN_GPIO_Port, TRIGGER_BTN_Pin);
        case E_BUTTON_ENCODER:
            return Button_getHardwareState(ENCODER_BTN_GPIO_Port, ENCODER_BTN_Pin);
        case E_BUTTON_SHOULDER_LEFT:
            // Do nothing
        case E_BUTTON_SHOULDER_RIGHT:
            // Do nothing
        default:
            ASSERT_MSG(FALSE, "in_eButton is invalid");
            return FALSE;
    }
    
}
