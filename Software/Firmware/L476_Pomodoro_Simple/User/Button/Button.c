#include "Button.h"
#include "MessageBroker.h"

static BOOL bButtonState = FALSE;

status_t Button_wasPressed(BOOL *pBButtonWasPressed)
{
    *pBButtonWasPressed = bButtonState;

    // Reset the button state after reading it
    bButtonState = FALSE;
    return STATUS_OK;
}

void Button_ISR(void)
{
    bButtonState = TRUE;
}

void Button_execute(void)
{
    BOOL bButtonWasPressed = FALSE;
    status_t tStatus = Button_wasPressed(&bButtonWasPressed);
    if (tStatus != STATUS_OK)
    {
        log_error("Button_wasPressed() failed with error code: %d", tStatus);
    }

    if (bButtonWasPressed == TRUE)
    {
        MessageBroker_message_t tMessage = {0};
        tMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED;
        tMessage.u16DataSize = 0;
        tMessage.au8DataBytes = NULL;
        status_t tStatus = MessageBroker_publish(tMessage);
        if (tStatus != STATUS_OK)
        {
            log_error("MessageBroker_publish() failed with error code: %d", tStatus);
        }
    }
}