#include "RealTimeClock.h"
#include "RealTimeClock_Hardware.h"
#include "MessageBroker.h"
#include "BlinkyLed.h"

STATIC BOOL bOneSecondPassed = FALSE;

STATIC status_t RealTimeClock_publishTimeAndDate(RealTimeClock_TimeAndDate_t *in_psTimeAndDate)
{
    MessageBroker_message_t tMessage = {0};
    tMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;
    tMessage.u16DataSize = TIME_AND_DATE_DATA_SIZE_BYTES;
    tMessage.au8DataBytes = (uint8_t *)in_psTimeAndDate;
    status_t tStatus = MessageBroker_publish(tMessage);
    if (tStatus != STATUS_OK)
    {
        log_error("MessageBroker_publish() failed with error code: %d", tStatus);
        return STATUS_UNKNOWN_ERR;
    }
    return STATUS_OK;
}

status_t RealTimeClock_execute(void)
{
    if (bOneSecondPassed == TRUE)
    {

        bOneSecondPassed = FALSE;

        /**
         * if one second has passed:
         * - Read the current time and date from the RTC HW
         * - Publish the data via the Message Broker
         */

        RealTimeClock_TimeAndDate_t tTimeAndDate = {0};
        status_t tStatus = RealTimeClockHW_getTimeAndDate(&tTimeAndDate);

        if (tStatus != STATUS_OK)
        {
            log_error("RealTimeClock_Hardware_getTimeAndDate() failed with error code: %d", tStatus);
            return STATUS_UNKNOWN_ERR;
        }

        tStatus = RealTimeClock_publishTimeAndDate(&tTimeAndDate);
        if (tStatus != STATUS_OK)
        {
            log_error("RealTimeClock_publishTimeAndDate() failed with error code: %d", tStatus);
            return STATUS_UNKNOWN_ERR;
        }
    }
    return STATUS_OK;
}

status_t RealTimeClock_callback(MessageBroker_message_t in_sMessage)
{
    if (in_sMessage.eMsgTopic == E_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSED)
    {
        bOneSecondPassed = TRUE;
    }
    return STATUS_OK;
}

void RealTimeClock_init(void)
{
    // Subscribe to the StopWatch topic
    status_t tStatus = MessageBroker_subscribe(E_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSED, RealTimeClock_callback);
    if (tStatus != STATUS_OK)
    {
        log_error("MessageBroker_subscribe() failed with error code: %d", tStatus);
    }
}