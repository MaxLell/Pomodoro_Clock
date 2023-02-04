#include "Main.h"
#include "Common.h"
#include "Rcc.h"
#include "BlinkyLed.h"
#include "SysTick.h"
#include "Button.h"

#ifdef TEST
int TestableMain(void)
#else
int main(void)
#endif
{
    printf("huhu\n");
    Rcc_init();
    SysTick_init();
    BlinkyLed_init();
    Button_init();

    while (TRUE)
    {
        Button_State button_state;
        button_state = Button_getState();
        if (button_state == BUTTON_PRESSED)
        {
            BlinkyLed_enable();
        }
        else
        {
            BlinkyLed_disable();
        }
    }
}
