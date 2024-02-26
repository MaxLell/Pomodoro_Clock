#include "RealTimeClock.h"

#include "Common.h"
#include "CountdownTimer.h"
#include "MessageBroker.h"
#include "RealTimeClock_Datatypes.h"
#include "RealTimeClock_Hardware.h"

STATIC timer_t tTimer;
STATIC status_e RealTimeClock_publishTimeAndDate(TimeAndDate_t *in_psTimeAndDate)
{
    { // Input Checks
        ASSERT_MSG(!(in_psTimeAndDate == NULL), "Null pointer provided");
    }
    msg_t sMsg = {0};
    sMsg.eMsgId = MSG_0300;
    sMsg.au8DataBytes = (uint8_t *)in_psTimeAndDate;
    sMsg.u16DataSize = sizeof(TimeAndDate_t);
    status_e tStatus = MessageBroker_publish(&sMsg);
    return tStatus;
}

status_e RealTimeClock_execute(void)
{
    timer_status_t eTimerStatus = Countdown_getTimerStatus(&tTimer);
    ASSERT_MSG(!(eTimerStatus == E_COUNTDOWN_TIMER_NOT_ENABLED), "Timer not enabled");

    if (eTimerStatus == E_COUNTDOWN_TIMER_NOT_EXPIRED)
    {
        return STATUS_OK;
    }
    else
    { // E_COUNTDOWN_TIMER_EXPIRED
        TimeAndDate_t tTimeAndDate = {0};
        status_e tStatus = RealTimeClockHW_getTimeAndDate(&tTimeAndDate);
        ASSERT_MSG(!(tStatus == STATUS_ERROR), "RTC Data could not get read");
        tStatus = RealTimeClock_publishTimeAndDate(&tTimeAndDate);
        ASSERT_MSG(!(tStatus == STATUS_ERROR), "Publishing caused an error");
    }
    return STATUS_OK;
}

void RealTimeClock_init(void)
{
    // Set up a countdown timer for one second
    Countdown_initTimerMs(&tTimer, 1000U, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&tTimer);
}