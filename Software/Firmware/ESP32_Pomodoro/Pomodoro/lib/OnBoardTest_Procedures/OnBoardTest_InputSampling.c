#include "OnBoardTest_InputSampling.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "InputSampling.h"

status_e OnBoardTest_InputSamplingTestMsgCb(const msg_t *const in_psMsg)
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

void OnBoardTest_InputSampling_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        Input Sampling Test");
    printf("%s\n", "************************************************************");

    // Create and run the Thread
    InputSampling_createTask();

    // Subscribe to the Module Messages, which are exececuted in the Thread
    // Button
    status_e eStatus;
    eStatus = MessageBroker_subscribe(MSG_0103, OnBoardTest_InputSamplingTestMsgCb);
    ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0103");
    unused(eStatus);
}

void OnBoardTest_InputSampling_execute(void)
{
    // Nothing much to be done here as everything is done in the thread
}