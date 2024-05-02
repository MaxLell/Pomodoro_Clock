#include "OnBoardTest_Pomodoro.h"
#include "Common.h"
#include "InputSampling.h"

#include "MessageBroker.h"
#include "MessageDefinitions.h"

status_e OnBoardTest_PomodoroTestMsgCb(const msg_t *const in_psMsg)
{
    { // Input Checks
        ASSERT_MSG(in_psMsg != NULL, "in_psMsg is NULL");
    }

    switch (in_psMsg->eMsgId)
    {

    case MSG_0103:
    {
        ButtonMessage_s *psButtonMessage = (ButtonMessage_s *)in_psMsg->au8DataBytes;
        if (psButtonMessage->eButton == E_BTN_TRIGGER)
        {
            if (psButtonMessage->eEvent == E_BTN_EVENT_SHORT_PRESSED)
            {
                log_info("Trigger Button pressed");

                // Publish the Pomodoro Start Message
                msg_t sMsg = {0};
                sMsg.eMsgId = MSG_0200;
                status_e eStatus = MessageBroker_publish(&sMsg);
                ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
                unused(eStatus); // Suppress the unused variable warning
            }
        }
    }
    break;

    case MSG_0200:
    {
        log_info("Pomodoro: Start Message Received");
    }
    break;

    case MSG_0201:
    {
        log_info("Pomodoro: Work Time Sequence Complete");
    }
    break;

    case MSG_0202:
    {
        log_info("Pomodoro: Break Time Sequence Complete");
    }
    break;

    case MSG_0203:
    {
        log_info("Pomodoro: Cancel Sequence Complete");
    }
    break;

    case MSG_0204:
    {
        log_info("Pomodoro: > Sequence Complete <");
    }
    break;

    default:
        ASSERT_MSG(false, "Unknown Message ID: %d", in_psMsg->eMsgId);
    }

    return STATUS_OK;
}

void OnBoardTest_Pomodoro_init(void)
{
    printf("%s\n", "************************************************************");
    printf("%s\n", "                        Pomodoro Test");
    printf("%s\n", "************************************************************");

    // Subscribe to the Messages
    status_e eStatus;
    { // Pomodoro Messages
        eStatus = MessageBroker_subscribe(MSG_0200, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0200");

        eStatus = MessageBroker_subscribe(MSG_0201, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0201");

        eStatus = MessageBroker_subscribe(MSG_0202, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0202");

        eStatus = MessageBroker_subscribe(MSG_0203, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0203");

        eStatus = MessageBroker_subscribe(MSG_0204, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0204");
    }

    { // Input Sampling Messages
        eStatus = MessageBroker_subscribe(MSG_0103, OnBoardTest_PomodoroTestMsgCb);
        ASSERT_MSG(STATUS_OK == eStatus, "Failed to subscribe to MSG_0103");
    }

    // Start the Input Sampling Task
    InputSampling_taskCreate();

    // Start the Pomodoro Task
}

void OnBoardTest_Pomodoro_execute(void)
{
}
