#include "StopWatch.h"
#include "main.h"
#include "MessageBroker.h"

extern TIM_HandleTypeDef htim6;
static BOOL oneSecondPassed = FALSE;

void StopWatch_delayMs(uint32_t delay)
{
    HAL_Delay(delay);
}

status_t StopWatch_oneSecondPassed(BOOL *bOneSecondPassed)
{
    if (bOneSecondPassed == NULL)
    {
        log_error("bOneSecondPassed is NULL");
        return STATUS_NULL_POINTER;
    }
    *bOneSecondPassed = oneSecondPassed;
    oneSecondPassed = FALSE;
    return STATUS_OK;
}

void StopWatch_ISR(void)
{
    oneSecondPassed = TRUE;
}

void StopWatch_init(void)
{
    // Start the HAL Timer 6
    HAL_TIM_Base_Start_IT(&htim6);
}

void StopWatch_execute(void)
{
    // When one second has passed, publish a message via the Message Broker
    if (oneSecondPassed == TRUE)
    {
        oneSecondPassed = FALSE;

        MessageBroker_message_t tMessage = {0};
        tMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSED;
        tMessage.u16DataSize = 0;
        tMessage.au8DataBytes = NULL;
        status_t tStatus = MessageBroker_publish(tMessage);
        if (tStatus != STATUS_OK)
        {
            log_error("MessageBroker_publish() failed with error code: %d", tStatus);
        }
    }
}