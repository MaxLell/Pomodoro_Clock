#include "CfgStore.h"

#include "MessageBroker.h"
#include "MessageIDs.h"
#include "MessageDefinitions.h"

/*********************************************
 * Private Data
 *********************************************/

status_e CfgStore_MsgCallback(const msg_t *const in_sMsg)
{
    switch (in_sMsg->eMsgId)
    {
    case MSG_0401:
    {
        // Publish the Pomodoro Configuration
        PomodoroPeriodConfiguration_s sPeriodCfg = {0};
        sPeriodCfg.bConfigWasUpdated = TRUE;
        sPeriodCfg.u8MinutesWorktimePeriod = 50;
        sPeriodCfg.u8MinutesBreaktimePeriod = 10;

        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0400;
        sMsg.au8DataBytes = (uint8_t *)&sPeriodCfg;
        sMsg.u16DataSize = sizeof(PomodoroPeriodConfiguration_s);
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }
    break;

    default:
        ASSERT_MSG(0, "Unknown Message ID: %d", in_sMsg->eMsgId);
        break;
    }
    return STATUS_OK;
}

void CfgStore_init(void)
{
    // Subscribe to the Request Pomodoro Configuration Message
    status_e eStatus = STATUS_OK;
    eStatus = MessageBroker_subscribe(MSG_0401, CfgStore_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0401");
    unused(eStatus); // To avoid compiler warning
}

void CfgStore_execute(void)
{
    // Do nothing (at least at the moment)
}