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
#include "PomodoroFsm.h"

/**
 * Static Variables
 */

// STATIC uint8_t u8WorktimeIntervalMin = 0;
// STATIC uint8_t u8BreaktimeIntervalMin = 0;

// STATIC uint8_t au8MinuteToColorArray[MINUTES_IN_HOUR] = {0};
// STATIC uint8_t au8LedToColorArray[TOTAL_LEDS] = {0};

// STATIC BOOL bSequenceWasInitialized = FALSE;
// STATIC uint8_t u8SequenceCounter = 0;
// STATIC BOOL bSequenceIsCompleted = TRUE;

// STATIC uint8_t u8CurrentMinute = MINUTES_IN_HOUR + 10;  // Gives it an impossible value
// STATIC uint8_t u8PreviousMinute = MINUTES_IN_HOUR + 10; // Gives it an impossible value

// STATIC uint8_t u8PFsmState = 100;         // Gives it an impossible value
// STATIC uint8_t u8LightControlState = 100; // Gives it an impossible value

// STATIC BOOL bPomodoroSequenceInitialized = FALSE;

// /**
//  * Static Function Prototypes
//  */

// STATIC status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
//                                                     uint8_t in_u8WorktimeIntervalMin,
//                                                     uint8_t in_u8BreaktimeIntervalMin,
//                                                     uint8_t *inout_au8ColorArray);

// STATIC status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
//                                                          uint8_t in_u8CurrentMinute);

// STATIC status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
//                                                  uint8_t *inout_au8LedToColorArray);

// STATIC status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray);

// /**
//  * Static Functions Definitions
//  */

// STATIC status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
//                                                     uint8_t in_u8WorktimeIntervalMin,
//                                                     uint8_t in_u8BreaktimeIntervalMin,
//                                                     uint8_t *inout_au8ColorArray)
// {
//     // Input Checks
//     assert_true(inout_au8ColorArray != NULL);

//     if (inout_au8ColorArray == NULL)
//     {
//         log_error("inout_au8ColorArray is NULL");
//         return STATUS_NULL_POINTER;
//     }

//     if (in_u8WorktimeIntervalMin >= MINUTES_IN_HOUR)
//     {
//         log_error("in_u8WorktimeIntervalMin is >= 60");
//         return STATUS_INVALID_ARG;
//     }

//     if (in_u8BreaktimeIntervalMin >= MINUTES_IN_HOUR)
//     {
//         log_error("in_u8BreaktimeIntervalMin is >= 60");
//         return STATUS_INVALID_ARG;
//     }

//     if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
//     {
//         log_error("in_u8CurrentMinute is >= 60");
//         return STATUS_INVALID_ARG;
//     }

//     uint8_t currentMinuteCounter = in_u8CurrentMinute;

//     // Write the Entries for the Work Time (with the respective offset)
//     for (uint8_t i = 0; i < in_u8WorktimeIntervalMin; i++)
//     {
//         inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_RED;
//         currentMinuteCounter++;
//         if (currentMinuteCounter >= MINUTES_IN_HOUR)
//         {
//             currentMinuteCounter = 0;
//         }
//     }

//     // Write the Entries for the Break Time
//     for (uint8_t i = 0; i < in_u8BreaktimeIntervalMin; i++)
//     {
//         inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_GREEN;
//         currentMinuteCounter++;
//         if (currentMinuteCounter >= MINUTES_IN_HOUR)
//         {
//             currentMinuteCounter = 0;
//         }
//     }

//     // Write the Entries for the Off Time
//     for (uint8_t i = 0; i < (MINUTES_IN_HOUR - in_u8WorktimeIntervalMin - in_u8BreaktimeIntervalMin); i++)
//     {
//         inout_au8ColorArray[currentMinuteCounter] = LIGHTCONTROL_LED_OFF;
//         currentMinuteCounter++;
//         if (currentMinuteCounter >= MINUTES_IN_HOUR)
//         {
//             currentMinuteCounter = 0;
//         }
//     }

//     return STATUS_OK;
// }

// status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
//                                           uint8_t *inout_au8LedToColorArray)
// {
//     // Input Checks
//     assert_true(in_au8MinuteToColorArray != NULL);
//     assert_true(inout_au8LedToColorArray != NULL);

//     if (in_au8MinuteToColorArray == NULL)
//     {
//         log_error("in_au8MinuteToColorArray is NULL");
//         return STATUS_NULL_POINTER;
//     }

//     if (inout_au8LedToColorArray == NULL)
//     {
//         log_error("inout_au8LedToColorArray is NULL");
//         return STATUS_NULL_POINTER;
//     }

//     // Calculate the number of LEDs per Minute
//     float u8LedsPerMinute = (float)TOTAL_LEDS / (float)MINUTES_IN_HOUR;
//     // printf("Leds per Minute: %f", u8LedsPerMinute);

//     // Fill the LED Array
//     for (float i = 0; i < MINUTES_IN_HOUR; i++)
//     {
//         uint8_t index = (uint8_t)(i * u8LedsPerMinute);
//         inout_au8LedToColorArray[(uint8_t)(i * u8LedsPerMinute)] = in_au8MinuteToColorArray[(uint8_t)i];
//     }
//     return STATUS_OK;
// }

// status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray)
// {
//     // Input Checks
//     assert_true(in_au8LedToColorArray != NULL);
//     if (in_au8LedToColorArray == NULL)
//     {
//         log_error("in_au8LedToColorArray is NULL");
//         return STATUS_NULL_POINTER;
//     }

//     // Set the LEDs to the respective color
//     for (uint8_t i = 0; i < TOTAL_LEDS; i++)
//     {
//         switch (in_au8LedToColorArray[i])
//         {
//         case LIGHTCONTROL_LED_OFF:
//             RgbLed_SetLedToColor(i, 0, 0, 0);
//             break;
//         case LIGHTCONTROL_LED_RED:
//             RgbLed_SetLedToColor(i, 255, 0, 0);
//             break;
//         case LIGHTCONTROL_LED_GREEN:
//             RgbLed_SetLedToColor(i, 0, 255, 0);
//             break;
//         case LIGHTCONTROL_LED_BLUE:
//             RgbLed_SetLedToColor(i, 0, 0, 255);
//             break;
//         default:
//             RgbLed_SetLedToColor(i, 0, 0, 0);
//             return STATUS_OVERFLOW;
//             log_error("Default case in LightControl_fillLedToRgbArray");
//             break;
//         }
//     }
//     return STATUS_OK;
// }

// status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
//                                                   uint8_t in_u8CurrentMinute)
// {
//     // Input Checks
//     assert_true(inout_au8MinuteToColorArray != NULL);
//     assert_true(in_u8CurrentMinute < MINUTES_IN_HOUR);

//     if (inout_au8MinuteToColorArray == NULL)
//     {
//         log_error("inout_au8MinuteToColorArray is NULL");
//         return STATUS_NULL_POINTER;
//     }

//     if (in_u8CurrentMinute >= MINUTES_IN_HOUR)
//     {
//         log_error("in_u8CurrentMinute is >= 60");
//         return STATUS_INVALID_ARG;
//     }

//     // Remove the Colors from the Minute Array
//     inout_au8MinuteToColorArray[in_u8CurrentMinute] = LIGHTCONTROL_LED_OFF;

//     return STATUS_OK;
// }

// status_t LightControl_initSequence(uint8_t in_u8CurrentMinute)
{
    status_t tStatus = STATUS_OK;

    // Get the Worktime Interval from the Config
    tStatus = Config_getWorktime(&u8WorktimeIntervalMin);

    // Get the Breaktime Interval from the Config
    tStatus = Config_getBreaktime(&u8BreaktimeIntervalMin);

    // Fill the Minute to Color Array)
    tStatus = LightControl_fillMinuteToColorArray(
        in_u8CurrentMinute,
        u8WorktimeIntervalMin,
        u8BreaktimeIntervalMin,
        au8MinuteToColorArray);

    // Set the sequence counter to u8WorktimeIntervalMin + u8BreaktimeIntervalMin
    u8SequenceCounter = u8WorktimeIntervalMin + u8BreaktimeIntervalMin;

    if (STATUS_OK != tStatus)
    {
        log_error("LightControl_initSequence failed");
        return tStatus;
    }
    else
    {
        return STATUS_OK;
    }
}

STATIC status_t LightControl_messageBrokerCallback(MessageBroker_message_t in_tMessage)
{
    switch (in_tMessage.eMsgTopic)
    {
    case E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE:
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
        E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE,
        LightControl_messageBrokerCallback);

    MessageBroker_subscribe(
        E_TOPIC_PFSM_STATE_CHANGED,
        LightControl_messageBrokerCallback);

    // Set internal States
    u8PFsmState = E_PFSM_STATE_IDLE;
    u8LightControlState = E_LCTRL_STATE_IDLE;
}

status_t LightControl_execute()
{
    return STATUS_OK;
}