#include "Button_Model.h"
#include "MessageBroker.h"

void Button_Model_publishData(BOOL in_bButtonEvent)
{
    check(in_bButtonEvent != FALSE, "The provided Button Event is FALSE. It should always be TRUE");

    MessageBroker_message_t tTriggerButtonMessage;

    /* Set the topic of the message */
    tTriggerButtonMessage.eMsgTopic = E_TRIGGER_BUTTON_EVENT;

    /**
     * Set the data of the message
     * For extra safety: When a module does only does a shallow
     * copy of the data, keep the data in static memory, so that
     * the provided Pointer does not dangle loose.
     */
    static uint32_t au32ButtonData[] = {TRUE};
    tTriggerButtonMessage.au32Data = au32ButtonData;

    /* Set the size of the message */
    tTriggerButtonMessage.u16DataSize = SIZE_OF(au32ButtonData);

    /* Publish the data */
    MessageBroker_publish(tTriggerButtonMessage);
error:
    log_error("Trigger Button Event was not published");
    return;
}