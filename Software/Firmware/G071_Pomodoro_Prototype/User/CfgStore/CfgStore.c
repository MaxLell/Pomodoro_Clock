#include "CfgStore.h"
#include "CfgStore_Datatypes.h"
#include "MessageBroker.h"
#include "MessageIDs.h"
#include "MessageDefinitions.h"

#define NOF_SETTINGS 3

static const TimeCfg_s sPomodoroTimingCfgStore[NOF_SETTINGS] = {
    [CFG_25_5] = {.u8WorktimeMinutes = 25, .u8BreaktimeMinutes = 5},
    [CFG_50_10] = {.u8WorktimeMinutes = 50, .u8BreaktimeMinutes = 10},
    [CFG_90_15] = {.u8WorktimeMinutes = 90, .u8BreaktimeMinutes = 15}};

STATIC PomodoroCfgSetting_e eCurrentSetting = CFG_90_15;

/*********************************************
 * Implementation
 *********************************************/

status_e
CfgStore_MsgCallback(const msg_t *const in_sMsg)
{
    switch (in_sMsg->eMsgId)
    {
    case MSG_0401:
    {
        // Publish the Pomodoro Configuration
        PomodoroPeriodConfiguration_s sPeriodCfg = {0};
        sPeriodCfg.bConfigWasUpdated = TRUE;
        sPeriodCfg.u8MinutesWorktimePeriod = sPomodoroTimingCfgStore[eCurrentSetting].u8WorktimeMinutes;
        sPeriodCfg.u8MinutesBreaktimePeriod = sPomodoroTimingCfgStore[eCurrentSetting].u8BreaktimeMinutes;

        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0400;
        sMsg.au8DataBytes = (uint8_t *)&sPeriodCfg;
        sMsg.u16DataSize = sizeof(PomodoroPeriodConfiguration_s);
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }
    break;

    case MSG_0402:
    {
        // Publish all Pomodoro Configurations
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0403;
        sMsg.au8DataBytes = (uint8_t *)&sPomodoroTimingCfgStore;
        sMsg.u16DataSize = sizeof(sPomodoroTimingCfgStore);
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }
    break;

    case MSG_0405:
    {
        // Publish the current Pomodoro Configuration
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0404;
        sMsg.au8DataBytes = (uint8_t *)&eCurrentSetting;
        status_e eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "MessageBroker_publish failed");
    }

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
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe");

    // Subscribe to the Request all Pomodoro Configurations Message
    eStatus = MessageBroker_subscribe(MSG_0402, CfgStore_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe");

    // Subscribe to Get Current Setting
    eStatus = MessageBroker_subscribe(MSG_0405, CfgStore_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe");

    unused(eStatus); // To avoid compiler warning
}

void CfgStore_execute(void)
{
    // Do nothing (at least at the moment)
}