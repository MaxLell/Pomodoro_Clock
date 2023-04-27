#include "LightEffects.h"
#include "MessageBroker.h"
#include "PomodoroFsm_Interface.h"
#include "LightEffects_Interface.h"
#include "Config.h"

#define MINUTES_IN_HOUR 60

STATIC uint8_t u8CurrentMinute = 0U;
STATIC uint8_t u8PFsmState = 0U;

#ifdef TEST
STATIC uint8_t au8TestPublishedLedArray[TOTAL_LEDS] = {0U};
#endif

/**
 * Function Prototypes
 */
STATIC void LightEffects_initMinuteToLedConfigArray(
    uint8_t in_u8CurrentMinute,
    uint8_t in_u8WorktimeIntervalMin,
    uint8_t in_u8BreaktimeIntervalMin,
    uint8_t *inout_au8MinuteToLedConfig);

STATIC void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                                     uint8_t in_u8CurrentMinute);

STATIC void LightEffects_scaleArray(
    uint8_t *in_au8SourceArray, uint8_t in_u8SourceArraySize,
    uint8_t *inout_au8TargetArray, uint8_t in_u8TargetArraySize);

STATIC void LightEffects_assembleLEDArray(
    uint8_t *in_au8OuterRingArray, uint8_t in_u8OuterRingArraySize,
    uint8_t *in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,
    uint8_t *in_au8InnerRingArray, uint8_t in_u8InnerRingArraySize,
    uint8_t *inout_au8AssembledLEDArray, uint8_t in_u8AssembledLEDArraySize);

STATIC void LightEffects_setScoreToArray(
    uint8_t in_u8Score,
    uint8_t *inout_au8ScoreArray,
    uint8_t in_u8ScoreArraySize);

STATIC void LightEffect_createAndPublishLedArray(
    uint8_t in_u8DailyPomodoroScore,
    uint8_t *in_au8MinuteToLedConfig);

/**
 * Function Definitions
 */

STATIC void LightEffects_initMinuteToLedConfigArray(
    uint8_t in_u8CurrentMinute,
    uint8_t in_u8WorktimeIntervalMin,
    uint8_t in_u8BreaktimeIntervalMin,
    uint8_t *inout_au8MinuteToLedConfig)
{
    // Input Checks
    assert_true(inout_au8MinuteToLedConfig != NULL);
    assert_true(
        (in_u8BreaktimeIntervalMin + in_u8WorktimeIntervalMin) <= TOTAL_MINUTES);
    assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);

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

STATIC void LightEffects_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
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

STATIC void LightEffects_scaleArray(
    uint8_t *in_au8SourceArray, uint8_t in_u8SourceArraySize,
    uint8_t *inout_au8TargetArray, uint8_t in_u8TargetArraySize)
{
    // Input Checks
    assert_true(in_au8SourceArray != NULL);
    assert_true(inout_au8TargetArray != NULL);
    assert_true(in_u8SourceArraySize > 0);
    assert_true(in_u8TargetArraySize > 0);

    // Calculate the Scale Factor
    float fScaleFactor = (float)in_u8SourceArraySize / (float)in_u8TargetArraySize;

    // Scale the Array
    for (uint8_t i = 0; i < in_u8TargetArraySize; i++)
    {
        inout_au8TargetArray[i] = in_au8SourceArray[(uint8_t)(i * fScaleFactor)];
    }
}

STATIC void LightEffects_assembleLEDArray(
    uint8_t *in_au8OuterRingArray, uint8_t in_u8OuterRingArraySize,
    uint8_t *in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,
    uint8_t *in_au8InnerRingArray, uint8_t in_u8InnerRingArraySize,
    uint8_t *inout_au8AssembledLEDArray, uint8_t in_u8AssembledLEDArraySize)
{
    // Input Checks
    assert_true(in_au8OuterRingArray != NULL);
    assert_true(in_au8MiddleRingArray != NULL);
    assert_true(in_au8InnerRingArray != NULL);
    assert_true(inout_au8AssembledLEDArray != NULL);
    assert_true(in_u8OuterRingArraySize > 0);
    assert_true(in_u8MiddleRingArraySize > 0);
    assert_true(in_u8InnerRingArraySize > 0);
    assert_true(in_u8AssembledLEDArraySize > 0);

    // Concatenate the Arrays into the Assembled Array
    for (uint8_t i = 0; i < in_u8AssembledLEDArraySize; i++)
    {
        if (i < in_u8OuterRingArraySize)
        {
            inout_au8AssembledLEDArray[i] = in_au8OuterRingArray[i];
        }
        else if (i < in_u8OuterRingArraySize + in_u8MiddleRingArraySize)
        {
            inout_au8AssembledLEDArray[i] = in_au8MiddleRingArray[i - in_u8OuterRingArraySize];
        }
        else
        {
            inout_au8AssembledLEDArray[i] = in_au8InnerRingArray[i - in_u8OuterRingArraySize - in_u8MiddleRingArraySize];
        }
    }
}

STATIC void LightEffects_setScoreToArray(
    uint8_t in_u8Score,
    uint8_t *inout_au8ScoreArray,
    uint8_t in_u8ScoreArraySize)
{
    // Input Checks
    assert_true(inout_au8ScoreArray != NULL);
    assert_true(in_u8ScoreArraySize > 0);
    assert_true(in_u8Score <= in_u8ScoreArraySize);

    // Set the Score to the Array
    for (uint8_t i = 0; i < in_u8Score; i++)
    {
        inout_au8ScoreArray[i] = LIGHTEFFECTS_LED_WHITE_LOW;
    }
    for (uint8_t i = in_u8Score; i < in_u8ScoreArraySize; i++)
    {
        inout_au8ScoreArray[i] = LIGHTEFFECTS_LED_OFF;
    }
}

STATIC void LightEffect_createAndPublishLedArray(
    uint8_t in_u8DailyPomodoroScore,
    uint8_t *in_au8MinuteToLedConfig)
{
    // Check inputs
    assert_true(in_au8MinuteToLedConfig != NULL);
    assert_true(in_u8DailyPomodoroScore <= MAX_POMODORO_SCORE);

    // outer ring
    uint8_t au8OuterRingArrayLed[TOTAL_LEDS_OUTER_RING] = {0};
    uint8_t au8OuterRingArrayMin[MINUTES_IN_HOUR] = {0};

    memcpy(au8OuterRingArrayMin, in_au8MinuteToLedConfig, MINUTES_IN_HOUR);

    // scale the Minute representation to the existing ring size
    LightEffects_scaleArray(
        au8OuterRingArrayMin,
        MINUTES_IN_HOUR,
        au8OuterRingArrayLed,
        TOTAL_LEDS_OUTER_RING);

    // middle ring
    uint8_t au8MiddleRingArray[TOTAL_LEDS_MIDDLE_RING] = {0};
    uint8_t au8MiddleRingArrayMin[MINUTES_IN_HOUR] = {0};

    memcpy(
        au8MiddleRingArrayMin,
        &in_au8MinuteToLedConfig[MINUTES_IN_HOUR], // Start Copy at offset
        MINUTES_IN_HOUR);

    // scale the Minute representation to the existing ring size
    LightEffects_scaleArray(
        au8MiddleRingArrayMin,
        MINUTES_IN_HOUR,
        au8MiddleRingArray,
        TOTAL_LEDS_MIDDLE_RING);

    // Inner Ring
    uint8_t au8InnerRingArray[TOTAL_LEDS_INNER_RING] = {0};

    // Calculate the score filling from the daily pomodoro score
    LightEffects_setScoreToArray(
        in_u8DailyPomodoroScore,
        au8InnerRingArray,
        TOTAL_LEDS_INNER_RING);

    // Assemble the LED Array
    uint8_t au8AssembledLEDArray[TOTAL_LEDS] = {0};
    LightEffects_assembleLEDArray(
        au8OuterRingArrayLed, TOTAL_LEDS_OUTER_RING,
        au8MiddleRingArray, TOTAL_LEDS_MIDDLE_RING,
        au8InnerRingArray, TOTAL_LEDS_INNER_RING,
        au8AssembledLEDArray, TOTAL_LEDS);

#ifdef TEST
    memcpy(au8TestPublishedLedArray, au8AssembledLEDArray, TOTAL_LEDS);
#endif

    // Publish the LED Array
    MessageBroker_message_t sMessage;
    sMessage.eMsgTopic = E_TOPIC_RING_LEDS_OUTPUT;
    sMessage.au8DataBytes = au8AssembledLEDArray;
    sMessage.u16DataSize = TOTAL_LEDS;

    MessageBroker_publish(sMessage);
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
