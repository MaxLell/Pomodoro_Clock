#include "Executer.h"

#include "Rcc.h"
#include "BlinkyLed.h"
#include "SysTick.h"
#include "Button_Conductor.h"
#include "MessageBroker.h"

status_t tDummyTriggerCallback(MessageBroker_message_t);
BOOL bTriggered = FALSE;

void Executer_init(void)
{
    Rcc_init();
    SysTick_init();
    BlinkyLed_init();
    Button_Conductor_init();
    MessageBroker_init();

    /**
     * Register the current dummy function as being the
     * Callback function of the Button Trigger
     */
    MessageBroker_subscribe(E_TRIGGER_BUTTON_EVENT, tDummyTriggerCallback);
}

status_t Executer_exec(void)
{

    /**
     * Run the Button Conductor
     * This polls on the ISR output.
     */
    Button_Conductor_exec();

    if (bTriggered == TRUE)
    {
        bTriggered = FALSE;
        BlinkyLed_toggle();
    }

    return STATUS_OK;
}

status_t tDummyTriggerCallback(MessageBroker_message_t tDummyMessage)
{
    bTriggered = TRUE;
    return STATUS_OK;
}