/**
 * @file LightControl.c
 * @brief LightControl does 3 things
 * 1. It receives the Arrays, which are to be displayed on the leds
 * 2. It assembles these arrays, into one large array, so that all leds can be set at once
 * 3. It forwards the assembled array to the RgbLed module
 * @author Maximilian Lell (maximilian.lell@gmail.com)
 */

#include "LightControl.h"
#include "RgbLed.h"
#include "Common.h"
#include "Config.h"
#include "MessageBroker.h"
#include "PomodoroFsm_Interface.h"

// Local Variables
static uint8_t u8CurrentMinute = 0;
static uint8_t u8PFsmState = 0;

STATIC status_t LightControl_messageBrokerCallback(MessageBroker_message_t in_tMessage)
{
    switch (in_tMessage.eMsgTopic)
    {
    case E_TOPIC_TIME_AND_DATE:
        // Parse the Minute from the data
        u8CurrentMinute = in_tMessage.au8DataBytes[1];
        break;
    case E_TOPIC_PFSM_STATE_CHANGED:

        // Parse the State from the data - Index 0 = New State
        u8PFsmState = in_tMessage.au8DataBytes[0];
        break;
    default:
        log_error("Unknown Message Topic");
        return STATUS_INVALID_ARG;
    }
    return STATUS_OK;
}

void LightControl_init()
{
    // Subscribe to the Message Broker Topics
    MessageBroker_subscribe(
        E_TOPIC_TIME_AND_DATE,
        LightControl_messageBrokerCallback);

    MessageBroker_subscribe(
        E_TOPIC_PFSM_STATE_CHANGED,
        LightControl_messageBrokerCallback);
}

status_t LightControl_execute()
{
    return STATUS_OK;
}