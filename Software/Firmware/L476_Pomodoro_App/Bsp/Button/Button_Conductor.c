#include "Button_Model.h"
#include "Button_Hardware.h"
#include "Button_Conductor.h"

void Button_Conductor_init()
{
    Button_Hardware_init();
}

status_t Button_Conductor_exec()
{
    BOOL bButtonWasPressed = Button_Hardware_wasPressed();
    if (bButtonWasPressed == TRUE)
    {
        Button_Model_publishData(bButtonWasPressed);
    }
}