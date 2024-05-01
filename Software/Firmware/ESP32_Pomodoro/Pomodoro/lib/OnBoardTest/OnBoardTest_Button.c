#include "OnBoardTest_Button.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "Button.h"
#include "Delay.h"

status_e OnBoardTest_ButtonTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");
    }

    switch (in_psMsg->eMsgId)
    {

    case MSG_0103:
    {
        // Print the score
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;

        // Map the correct button to the button number
        char *pcButtonNames[] = {"Invalid", "Trigger Btn"};

        // Map the correct event to the event number
        char *pcEventNames[] = {"Invalid", "Pressed", "Released", "Long Pressed"};

        log_info("Button: %s, Event: %s", pcButtonNames[psButtonMessage->eButton], pcEventNames[psButtonMessage->eEvent]);
    }
    break;

    default:
        ASSERT_MSG(false, "Unknown Message ID: %d", in_psMsg->eMsgId);
    }

    return STATUS_OK;
}

void OnBoardTest_Button_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        Button Test");
    printf("%s\n", "************************************************************");

    // Initialize the button hardware
    Button_init();

    // Subscribe to the Button Event Message from the Message Broker
    status_e eStatus;
    eStatus = MessageBroker_subscribe(MSG_0103, OnBoardTest_ButtonTestMsgCb);
    ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0103");
    unused(eStatus);
}

void OnBoardTest_Button_execute(void)
{
    // Execute the button functionality
    Button_execute();

    // The sampling shall happen every 1ms
    Delay_ms(1);
}