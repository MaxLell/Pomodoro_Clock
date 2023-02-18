#include "Button_Hardware.h"
#include "GPIO.h"
#include "EXTI.h"

void Button_Hardware_init()
{
    GPIO_PushButtonPC13_init();
    EXTI_PushButtonPC13_init();
}

BOOL Button_Hardware_wasPressed()
{
    return EXTI_PushButtonPC13_wasPressed();
}