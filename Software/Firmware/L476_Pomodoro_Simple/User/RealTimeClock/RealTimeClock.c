#include "RealTimeClock.h"
#include "RealTimeClock_Hardware.h"
#include "MessageBroker.h"
#include "BlinkyLed.h"

STATIC BOOL bOneSecondPassed = FALSE;

status_t RealTimeClock_execute(void)
{
    if (bOneSecondPassed == TRUE)
    {
        /**
         * if one second has passed:
         * - Read the current minute from the RTC
         * - Publish the current minute via the Message Broker
         */

        bOneSecondPassed = FALSE;

        uint8_t u8Minute = 0;

        status_t tStatus = RealTimeClock_getCurrentMinute(&u8Minute);
        if (tStatus != STATUS_OK)
        {
            log_error("RealTimeClock_getCurrentMinute() failed with error code: %d", tStatus);
            return STATUS_UNKNOWN_ERR;
        }

        MessageBroker_message_t tMessage = {0};
        tMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_CURRENT_MINUTE;
        tMessage.u16DataSize = 1;
        tMessage.au8DataBytes = &u8Minute;
        tStatus = MessageBroker_publish(tMessage);
        if (tStatus != STATUS_OK)
        {
            log_error("MessageBroker_publish() failed with error code: %d", tStatus);
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