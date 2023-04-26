#include "LightEffects.h"
#include "MessageBroker.h"
#include "PomodoroFsm_Interface.h"
#include "LightEffects_Interface.h"
#include "Config.h"

#define MINUTES_IN_HOUR 60

STATIC uint8_t u8CurrentMinute = 0U;
STATIC uint8_t u8PFsmState = 0U;

void LightEffects_initMinuteToLedConfigArray(
    uint8_t in_u8CurrentMinute,
    uint8_t in_u8WorktimeIntervalMin,
    uint8_t in_u8BreaktimeIntervalMin,
    uint8_t *inout_au8MinuteToLedConfig)
{
    // Input Checks
    assert_true(inout_au8MinuteToLedConfig != NULL);
    assert_true(
        (in_u8BreaktimeIntervalMin + in_u8WorktimeIntervalMin) <= TOTAL_MINUTES);

    uint8_t currentIndex = in_u8CurrentMinute;
    uint8_t remainingWorktimeMin = in_u8WorktimeIntervalMin;
    uint8_t remainingBreaktimeMin = in_u8BreaktimeIntervalMin;
    BOOL bOneRingCompleted = FALSE;

    // Fill the array with the LED OFF
    for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    {
        inout_au8MinuteToLedConfig[i] = LIGHTEFFECTS_LED_OFF;
    }

    // Fill in the worktime
    while (remainingWorktimeMin > 0)
    {
        remainingWorktimeMin--;
        inout_au8MinuteToLedConfig[currentIndex] = LIGHTEFFECTS_LED_RED_LOW;

        currentIndex++;
        if (currentIndex == in_u8CurrentMinute)
        {
            bOneRingCompleted = TRUE;
            currentIndex += MINUTES_IN_HOUR;
        }
        if ((currentIndex > MINUTES_IN_HOUR - 1) && (!bOneRingCompleted))
        {
            currentIndex = 0;
        }
        if ((currentIndex >= TOTAL_MINUTES) && (bOneRingCompleted))
        {
            currentIndex = MINUTES_IN_HOUR;
        }
    }

    // Fill in the breaktime
    while (remainingBreaktimeMin > 0)
    {
        remainingBreaktimeMin--;

        inout_au8MinuteToLedConfig[currentIndex] = LIGHTEFFECTS_LED_GREEN_LOW;

        currentIndex++;
        if (currentIndex == in_u8CurrentMinute)
        {
            bOneRingCompleted = TRUE;
            currentIndex += MINUTES_IN_HOUR + 1;
        }
        if ((currentIndex > MINUTES_IN_HOUR - 1) && (!bOneRingCompleted))
        {
            currentIndex = 0;
        }
        if ((currentIndex >= TOTAL_MINUTES) && (bOneRingCompleted))
        {
            currentIndex = MINUTES_IN_HOUR;
        }
    }
}

void LightEffects_transformMinuteToLedConfigArrayToLedConfigArray(
    uint8_t *in_au8MinuteToLedConfigArray,
    uint8_t *inout_au8LedConfigArray)
{
    // Input Checks
    assert_true(in_au8MinuteToLedConfigArray != NULL);
    assert_true(inout_au8LedConfigArray != NULL);

    // Calculate the number of LEDs per Minute
    float fLedsPerMinute = (float)TOTAL_LEDS / (float)TOTAL_MINUTES;

    // Fill the LED Config Array for the outer Ring
    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        inout_au8LedConfigArray[(uint8_t)(i * fLedsPerMinute)] = in_au8MinuteToLedConfigArray[(uint8_t)i];
    }
}

void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                              uint8_t in_u8CurrentMinute)
{
    // Input Checks
    assert_true(inout_au8MinuteToColorArray != NULL);
    assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);

    // Remove the Colors from the Minute Array
    inout_au8MinuteToColorArray[in_u8CurrentMinute] = LIGHTEFFECTS_LED_OFF;
}

STATIC status_t LightEffects_messageBrokerCallback(
    MessageBroker_message_t in_pMessage)
{
    switch (in_pMessage.eMsgTopic)
    {
    case E_TOPIC_TIME_AND_DATE:
        /* Get the Current Minute */
        u8CurrentMinute = in_pMessage.au8DataBytes[1];
        break;
    case E_TOPIC_PFSM_STATE_CHANGED:
        /* Get the Current PFSM State */
        u8PFsmState = in_pMessage.au8DataBytes[0]; // New State
        break;
    default:
        /* Unknown Topic */
        log_error("Unknown Message Topic");
        return STATUS_INVALID_ARG;
        break;
    }
    return STATUS_OK;
}

void LightEffects_init()
{
    /* Subscribe to the current Minute */
    MessageBroker_subscribe(
        E_TOPIC_TIME_AND_DATE,
        LightEffects_messageBrokerCallback);

    /* Subscribe to the current PFSM State */
    MessageBroker_subscribe(
        E_TOPIC_PFSM_STATE_CHANGED,
        LightEffects_messageBrokerCallback);

    /* Initialize the PFSM State */
    u8PFsmState = E_PFSM_STATE_IDLE;

    /* Initialize the Current Minute */
    u8CurrentMinute = 100U;
}

status_t LightEffects_execute()
{
    /* Run the Statemachine */
    switch (u8PFsmState)
    {
    case E_PFSM_STATE_SEEKING_ATTENTION:
        break;

    case E_PFSM_STATE_IDLE:

        break;

    case E_PFSM_STATE_WORKTIME:

        break;
    case E_PFSM_STATE_BREAKTIME:

        break;

    default:
        log_error("Unknown PFSM State");
        return STATUS_INVALID_ARG;
        break;
    }
    return STATUS_OK;
}
