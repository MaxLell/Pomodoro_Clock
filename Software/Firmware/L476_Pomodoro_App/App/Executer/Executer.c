#include "Executer.h"

#include "Rcc.h"
#include "BlinkyLed.h"
#include "SysTick.h"
#include "Button.h"

void Executer_init(void)
{
    Rcc_init();
    SysTick_init();
    BlinkyLed_init();
    Button_init();
}

status_t Executer_exec(void)
{
    /**
     * Place the application Logic here
     */
    return STATUS_OK;
}
