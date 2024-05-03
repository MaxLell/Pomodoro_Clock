#include "OnBoardTest_SeekingAttention.h"
#include "SeekingAttentionTask.h"
#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "InputSampling.h"
#include "Delay.h"

status_e OnBoardTest_testSeekingAttentionMsgCb(const msg_t *const in_psMsg)
{
    // Input Checks
    ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");

    switch (in_psMsg->eMsgId)
    {
    case MSG_0103:
    {
        status_e eStatus;
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;

        if (E_BTN_TRIGGER == psButtonMessage->eButton)
        {
            if (E_BTN_EVENT_SHORT_PRESSED == psButtonMessage->eEvent)
            {
                // Publish the Seeking Attention Start Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0900;
                eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning

                log_info("Seeking Attention Command: Start");
            }
            if (E_BTN_EVENT_RELEASED == psButtonMessage->eEvent)
            {
                // Publish the Seeking Attention Stop Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0901;
                eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning

                log_info("Seeking Attention Command: Stop");
            }
        }
    }
    break;

    case MSG_0902:
    {
        log_info("Seeking Attention is now finished");
    }
    break;

    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
    }

    return STATUS_OK;
}

void OnBoardTest_SeekingAttention_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        Seeking Attention Test");
    printf("%s\n", "In order to run this test: ");
    printf("%s\n", "1. Keep the Trigger Btn pressed to start the Seeking Attention");
    printf("%s\n", "2. Release the Trigger Btn to stop the Seeking Attention");
    printf("%s\n", "************************************************************");

    status_e eStatus;
    // Start the SeekingAttention task
    SeekingAttentionTask_createTask();

    // Start the InputSampling task
    InputSampling_createTask();

    // Wait for 10msec until everything is initialized
    Delay_ms(10);

    { // Publish the Test Message (Needs to be after the Seeking Attention Init function!!!)
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0005;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }

    { // Subscribe to Messages
        // Subscribe to the Button Event
        eStatus = MessageBroker_subscribe(MSG_0103, OnBoardTest_testSeekingAttentionMsgCb);
        ASSERT_MSG(eStatus == STATUS_OK, "MessageBroker_subscribe failed");

        // Subscribe to the SeekingAttention Finished Message
        eStatus = MessageBroker_subscribe(MSG_0902, OnBoardTest_testSeekingAttentionMsgCb);
        ASSERT_MSG(eStatus == STATUS_OK, "MessageBroker_subscribe failed");
    }

    unused(eStatus);
}

void OnBoardTest_SeekingAttention_execute(void)
{
    // Nothing much to be done here
}