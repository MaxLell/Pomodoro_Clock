#include "Main.h"
#include "Common.h"
#include "Rcc.h"
#include "BlinkyLed.h"
#include "SysTick.h"
// #include "stm32l4xx.h"

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

    while (TRUE)
    {
        BlinkyLed_toggle();
        delay_ms(100);
    }
}
