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
    uint8_t *inout_au8MinuteToLedConfigArray)
{
    // Input Checks
    assert_true(inout_au8MinuteToLedConfigArray != NULL);
    assert_true(in_u8WorktimeIntervalMin <= MINUTES_IN_HOUR);
    assert_true(in_u8BreaktimeIntervalMin <= MINUTES_IN_HOUR);
    assert_true(
        (in_u8WorktimeIntervalMin + in_u8BreaktimeIntervalMin) <= MINUTES_IN_HOUR);

    uint8_t currentMinuteCounter = in_u8CurrentMinute;

    // Write the Entries for the Work Time (with the respective offset)
    for (uint8_t i = 0; i < in_u8WorktimeIntervalMin; i++)
    {
        inout_au8MinuteToLedConfigArray[currentMinuteCounter] = LIGHTEFFECTS_LED_RED_LOW;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
        }
    }

    // Write the Entries for the Break Time
    for (uint8_t i = 0; i < in_u8BreaktimeIntervalMin; i++)
    {
        inout_au8MinuteToLedConfigArray[currentMinuteCounter] = LIGHTEFFECTS_LED_GREEN_LOW;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
        }
    }

    // Write the Entries for the Off Time
    for (
        uint8_t i = 0;
        i < (MINUTES_IN_HOUR - in_u8WorktimeIntervalMin - in_u8BreaktimeIntervalMin);
        i++)
    {
        inout_au8MinuteToLedConfigArray[currentMinuteCounter] = LIGHTEFFECTS_LED_OFF;
        currentMinuteCounter++;
        if (currentMinuteCounter >= MINUTES_IN_HOUR)
        {
            currentMinuteCounter = 0;
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
    float fLedsPerMinute = (float)TOTAL_LEDS_OUTER_RING / (float)MINUTES_IN_HOUR;

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
