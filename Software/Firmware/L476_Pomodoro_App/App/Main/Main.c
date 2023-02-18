#include "Main.h"
#include "Common.h"
#include "Rcc.h"
#include "BlinkyLed.h"
#include "SysTick.h"
#include "Button.h"
#include "Executer.h"

#ifdef TEST
int testableMain(void)
#else
int main(void)
#endif
{
    // printf("huhu\n");
    // Rcc_init();
    // SysTick_init();
    // BlinkyLed_init();
    // Button_init();

    Executer_init();

    while (Executer_exec() == STATUS_OK)
    {
        /**
         * Run the application in the Executer_exec()
         */
    }
}
