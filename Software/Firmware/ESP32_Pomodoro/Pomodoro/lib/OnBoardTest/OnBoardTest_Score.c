#include "OnBoardTest_Score.h"
#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "Delay.h"

#include "InputSampling.h"
#include "ScoreTask.h"

status_e OnBoardTest_ScoreTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");
    }

    switch (in_psMsg->eMsgId)
    {
    case MSG_0103: // Button Event Message
    {
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;
        if (psButtonMessage->eButton == E_BTN_TRIGGER)
        {
            if (psButtonMessage->eEvent == E_BTN_EVENT_SHORT_PRESSED)
            {
                // Publish the Pomodoro Start Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0200;
                status_e eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning
                log_info("Pomodoro Start Message Sent");
            }
            if (psButtonMessage->eEvent == E_BTN_EVENT_RELEASED)
            {
                // Publish the Pomodoro Complete Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0204;
                status_e eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning
                log_info("Pomodoro Complete Message Sent");
            }
        }
    }
    break;
    default:
        ASSERT_MSG(NULL, "Unknown Message ID: %d", in_psMsg->eMsgId);
        break;
    }

    return STATUS_OK;
}

void OnBoardTest_Score_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        Score Test");
    printf("%s\n", "************************************************************");

    // Subscribe to the Button Messages (these are used to trigger the input events for the Score Thread)
    status_e eStatus = STATUS_ERROR;
    eStatus = MessageBroker_subscribe(MSG_0103, OnBoardTest_ScoreTestMsgCb);
    ASSERT_MSG(eStatus == STATUS_OK, "MessageBroker_subscribe failed");

    // Create the Score Task (it should do everything by itself)
    ScoreTask_createTask();

    // Create the Input Sampling Task
    InputSampling_createTask();

    // Wait for 10msec until the Tasks are established
    Delay_ms(10);

    // Send out the Test Message to speed up the procedure
    {
        const u32 FIFTY_MSEC = 50;
        const u32 TWENTY_SECONDS = 20000;
        const u32 THIRTY_SECONDS = 30000;
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0006;
        TestData_0006_s sScoreTimeStamps = {0};
        sScoreTimeStamps.u32MinutePeriod = FIFTY_MSEC;
        sScoreTimeStamps.u32TimeoutPeriod = TWENTY_SECONDS;  // Display of the Score is Switched Off
        sScoreTimeStamps.u32WatchdogPeriod = THIRTY_SECONDS; // The Score is Reset
        sMsg.au8DataBytes = (uint8_t *)&sScoreTimeStamps;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        log_info("Test Config Message Sent");
    }
    unused(eStatus);
}

void OnBoardTest_Score_execute(void)
{
    // Nothing much to be done here - everything from this test is executed automatically in the Background by the Task itself.
}