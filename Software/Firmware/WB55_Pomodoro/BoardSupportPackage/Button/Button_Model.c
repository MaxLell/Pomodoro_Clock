#include "Button_Model.h"
#include "MessageBroker.h"

void Button_Model_publishData(BOOL in_bButtonEvent)
{
    assert_true(in_bButtonEvent == TRUE);

    MessageBroker_message_t tTriggerButtonMessage;

    /* Set the topic of the message */
    tTriggerButtonMessage.eMsgTopic = E_TRIGGER_BUTTON_EVENT;

    uint32_t au32ButtonData[] = {TRUE};
    tTriggerButtonMessage.au32Data = au32ButtonData;

    /* Set the size of the message */
    tTriggerButtonMessage.u16DataSize = SIZE_OF(au32ButtonData);

    /* Publish the data */
    MessageBroker_publish(tTriggerButtonMessage);
}