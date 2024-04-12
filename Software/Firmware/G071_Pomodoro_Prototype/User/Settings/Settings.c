#include "Settings.h"
#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"

STATIC TimeCfg_s *psTimeCfg = NULL;
STATIC uint8_t u8NofSettings = 0;

status_e
Settings_MsgCallback(const msg_t *const in_sMsg)
{
    switch (in_sMsg->eMsgId)
    {
    case MSG_0700: // Start Settings Message
    {
        // Publish the Reset Encoder Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0600;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
        log_info("Reset Encoder Message published");
    }
    break;

    case MSG_0403:
    {
        // Receive all Pomodoro Configurations
        psTimeCfg = (TimeCfg_s *)in_sMsg->au8DataBytes;
        u8NofSettings = in_sMsg->u16DataSize / sizeof(TimeCfg_s);
    }
    break;

    default:
        break;
    }

    return STATUS_OK;
}

void Settings_init(void)
{
    // Subscribe to the Start Settings Message
    status_e eStatus;
    eStatus = MessageBroker_subscribe(MSG_0700, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0501");

    // Subscribe to the CfgStore Message (Response to the Request to recieve all Pomodoro Configurations)
    eStatus = MessageBroker_subscribe(MSG_0403, Settings_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0403");

    // Publish the Reset Encoder Message
}

void Settings_execute(void)
{
}
