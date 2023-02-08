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
        BOOL button_pressed = FALSE;

        button_pressed = Button_wasPressedSinceLastRead();

        if (button_pressed == TRUE)
        {
            for (uint8_t i = 0; i < 100; i++)
            {
                BlinkyLed_toggle();
                delay_ms(10);
            }
            button_pressed = FALSE;
        }
        else
        {
            BlinkyLed_disable();
        }
    }
}
