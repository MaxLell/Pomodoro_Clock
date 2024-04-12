#include "CfgStore.h"

#include "MessageBroker.h"
#include "MessageIDs.h"
#include "MessageDefinitions.h"

typedef enum
{
    SETTING_25_5 = 0,
    SETTING_50_10,
    SETTING_90_15,
    SETTING_LAST
} PomodoroSettings_e;

#define NOF_SETTINGS 3

TimeCfg_s sPomodoroTimingCfgStore[NOF_SETTINGS] = {
    [SETTING_25_5] = {.u8WorktimeMinutes = 25, .u8BreaktimeMinutes = 5},
    [SETTING_50_10] = {.u8WorktimeMinutes = 50, .u8BreaktimeMinutes = 10},
    [SETTING_90_15] = {.u8WorktimeMinutes = 90, .u8BreaktimeMinutes = 15}};

STATIC PomodoroSettings_e eCurrentSetting = SETTING_25_5;

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