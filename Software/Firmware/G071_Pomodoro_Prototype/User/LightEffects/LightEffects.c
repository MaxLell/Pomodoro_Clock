#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

#include "PomodoroControl_Datatypes.h"

#include "CountdownTimer.h"
#include "Delay.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"
#include "math.h"

/************************************************************
 * Function Prototypes
 ************************************************************/

/************************************************************
 * Implementation
 ************************************************************/

void LightEffects_scaleArray(const uint8_t *const in_au8SourceArray, uint8_t in_u8SourceArraySize,
                             uint8_t *out_au8TargetArray, uint8_t in_u8TargetArraySize)
{
    { // Input Checks
        ASSERT_MSG(!(in_au8SourceArray == NULL), "in_au8SourceArray is NULL Ptr");
        ASSERT_MSG(!(out_au8TargetArray == NULL), "in_au8SourceArray is NULL Ptr");
        ASSERT_MSG(!(in_u8SourceArraySize == 0), "Provided in_u8SourceArraySize needs to be larger then 0");
        ASSERT_MSG(!(in_u8TargetArraySize == 0), "Provided in_u8TargetArraySize needs to be larger then 0");
    }

    // Calculate the Scale Factor
    float fScaleFactor = (float)in_u8SourceArraySize / (float)in_u8TargetArraySize;
    // Scale the Array
    for (uint8_t i = 0; i < in_u8TargetArraySize; i++)
    {
        out_au8TargetArray[i] = in_au8SourceArray[(uint8_t)(i * fScaleFactor)];
    }
}
void LightEffects_DotAroundTheCircle(status_e *out_eSequenceStatus, uint16_t u16PeriodPerIncrementMs)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == out_eSequenceStatus), "Sequence Status cannot be NULL");
        ASSERT_MSG(!(u16PeriodPerIncrementMs == 0U), "Period cannot be 0");
    }
    // Variable Declarations
    static uint8_t u8LedIndex = 0;
    uint8_t effect[RGB_LED_TOTAL_LEDS] = {2, 5, 5, 5, 2};
    uint8_t effect_size = sizeof(effect);

    // Increment the ledIndex
    u8LedIndex++;

    if (u8LedIndex == RGB_LED_TOTAL_LEDS)
    {
        // Set the sequence status to complete
        *out_eSequenceStatus = STATUS_PENDING;

        // Reset the ledIndex
        u8LedIndex = 0;

        // Disable all LEDs
        RgbLed_clear();
    }
    else
    {
        for (uint8_t i = 0; i < RGB_LED_TOTAL_LEDS; i++)
        {
            RgbLed_setPixelColor(i, 0, 0, 0);
        }

        for (uint8_t i = 0; i < effect_size; i++)
        {
            uint8_t tmp = (u8LedIndex + i) % RGB_LED_TOTAL_LEDS;
            RgbLed_setPixelColor(tmp, effect[i], effect[i], effect[i]);
        }

        // Set the Sequence Status to in progress
        *out_eSequenceStatus = STATUS_PENDING;
    }
    // Wait a fixed delay
    Delay_ms(u16PeriodPerIncrementMs);

    // Show the sequence on the LEDs
    RgbLed_show();
}

void LightEffects_ClearAllRingLeds(void)
{
    RgbLed_clear();
    Delay_ms(10);
    RgbLed_show();
}

/************************************************************
 * Implementation for the Pomodoro
 ************************************************************/

void LightEffects_RenderRings(const uint8_t *const in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,
                              const uint8_t *const in_au8OuterRingArray, uint8_t in_u8OuterRingArraySize)
{
    { // Input Checks
        ASSERT_MSG(!(in_au8MiddleRingArray == NULL), "in_au8MiddleRingArray is NULL");
        ASSERT_MSG(!(in_u8MiddleRingArraySize == 0), "in_u8MiddleRingArraySize is 0");
        ASSERT_MSG(!(in_u8MiddleRingArraySize != NOF_LEDS_MIDDLE_RING),
                   "in_u8MiddleRingArraySize is not equal to NOF_LEDS_MIDDLE_RING");
        ASSERT_MSG(!(in_au8OuterRingArray == NULL), "in_au8OuterRingArray is NULL");
        ASSERT_MSG(!(in_u8OuterRingArraySize == 0), "in_u8OuterRingArraySize is 0");
        ASSERT_MSG(!(in_u8OuterRingArraySize != NOF_LEDS_OUTER_RING), "in_u8OuterRingArraySize is not equal to "
                                                                      "NOF_LEDS_OUTER_RING");
    }
    // Render the Outer Ring
    uint8_t u8LedIndex = START_INDEX_OUTER_RING;
    for (uint8_t i = 0; i < in_u8OuterRingArraySize; i++)
    {
        switch (in_au8OuterRingArray[i])
        {
        case E_ANIMATION_OFF:
            RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
            break;
        case E_ANIMATION_WORK_TIME:
            RgbLed_setPixelColor(u8LedIndex, 5, 0, 0);
            break;
        case E_ANIMATION_BREAK_TIME:
            RgbLed_setPixelColor(u8LedIndex, 0, 5, 0);
            break;
        case E_ANIMATION_BREAK_TIME_BRIGHT:
            RgbLed_setPixelColor(u8LedIndex, 0, 100, 0);
            break;
        case E_ANIMATION_FLASHLIGHT:
            RgbLed_setPixelColor(u8LedIndex, 100, 100, 100);
            break;
        case E_ANIMATION_CANCEL_SEQUENCE:
            RgbLed_setPixelColor(u8LedIndex, 100, 0, 200);
            break;
        default:
            ASSERT_MSG(FALSE, "Unknown Animation Type");
            break;
        }
        u8LedIndex++;
    }

    uint8_t tmp = START_INDEX_MIDDLE_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    // Render the Middle ring
    for (uint8_t i = 0; i < in_u8MiddleRingArraySize; i++)
    {
        switch (in_au8MiddleRingArray[i])
        {
        case E_ANIMATION_OFF:
            RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
            break;
        case E_ANIMATION_WORK_TIME:
            RgbLed_setPixelColor(u8LedIndex, 5, 0, 0);
            break;
        case E_ANIMATION_WARNING:
            RgbLed_setPixelColor(u8LedIndex, 5, 5, 0);
            break;
        case E_ANIMATION_BREAK_TIME:
            RgbLed_setPixelColor(u8LedIndex, 0, 5, 0);
            break;
        case E_ANIMATION_BREAK_TIME_BRIGHT:
            RgbLed_setPixelColor(u8LedIndex, 0, 100, 0);
            break;
        case E_ANIMATION_FLASHLIGHT:
            RgbLed_setPixelColor(u8LedIndex, 100, 100, 100);
            break;
        case E_ANIMATION_CANCEL_SEQUENCE:
            RgbLed_setPixelColor(u8LedIndex, 100, 0, 200);
            break;
        default:
            ASSERT_MSG(FALSE, "Unknown Animation Type");
            break;
        }
        u8LedIndex++;
    }

    tmp = START_INDEX_INNER_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    RgbLed_show();
}

void LightEffects_ClearPomodoroProgressRings(void)
{
    // Clear the LEDs of the OUTER RING
    uint8_t u8LedIndex = START_INDEX_OUTER_RING;
    for (uint8_t i = 0; i < NOF_LEDS_OUTER_RING; i++)
    {
        RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
        u8LedIndex++;
        RgbLed_show();
    }

    ASSERT_MSG(!(u8LedIndex != START_INDEX_MIDDLE_RING), "u8LedIndex is not equal to %d. It is instead %d",
               START_INDEX_MIDDLE_RING, u8LedIndex);

    // Clear the LEDs of the MIDDLE RING
    u8LedIndex = START_INDEX_MIDDLE_RING;
    for (uint8_t i = 0; i < NOF_LEDS_MIDDLE_RING; i++)
    {
        RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
        u8LedIndex++;
        RgbLed_show();
    }
    ASSERT_MSG(!(u8LedIndex != START_INDEX_INNER_RING), "u8LedIndex is not equal to %d. It is instead %d",
               START_INDEX_INNER_RING, u8LedIndex);

    Delay_ms(10); // TODO: Fix the Bug, which makes it necessary to wait here

    RgbLed_show();
}

void LightEffects_RenderPomodoro(const uint8_t *const in_au8MinuteArray, const uint8_t in_u8ArraySize,
                                 BOOL bIsWorktimeOver)
{
    {
        // Input Checks
        ASSERT_MSG(!(in_au8MinuteArray == NULL), "in_au8MinuteArray is NULL");
        ASSERT_MSG(!(in_u8ArraySize == 0), "in_u8ArraySize is 0");
    }

    /**
     * Check if there are any entries with WT remaining in the au8Minute Array
     * YES: set the internal mode to Breaktime
     * NO: set the internal mode to Worktime
     */

    // Create a Minute Array filled with the animation types
    uint8_t au8AnimationArray[TOTAL_MINUTES] = {0};
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
    {
        switch (in_au8MinuteArray[i])
        {
        case E_CFG_WORKTIME:
            au8AnimationArray[i] = E_ANIMATION_WORK_TIME;
            ASSERT_MSG(!(TRUE == bIsWorktimeOver),
                       "Worktime is over - there should be no entires with Worktime in the Minute Array");
            break;

        case E_CFG_BREAKTIME:
            au8AnimationArray[i] = bIsWorktimeOver ? E_ANIMATION_BREAK_TIME_BRIGHT : E_ANIMATION_BREAK_TIME;
            break;

        case E_CFG_OFF:
            au8AnimationArray[i] = E_ANIMATION_OFF;
            break;

        default:
            ASSERT_MSG(FALSE, "Unknown Animation Type");
            break;
        }
    }

    // if the Worktime is over, set the animation to flashlight on the inner ring
    if (bIsWorktimeOver)
    {
        for (uint8_t i = MINUTES_IN_HOUR; i < TOTAL_MINUTES; i++)
        {
            au8AnimationArray[i] = E_ANIMATION_FLASHLIGHT;
        }
    }

    // Compress the Array
    uint8_t au8CompressedArrayRingOuter[NOF_LEDS_OUTER_RING] = {0};
    uint8_t au8CompressedArrayRingMiddle[NOF_LEDS_MIDDLE_RING] = {0};
    LightEffects_scaleArray(au8AnimationArray, MINUTES_IN_HOUR, au8CompressedArrayRingOuter, NOF_LEDS_OUTER_RING);
    LightEffects_scaleArray(&au8AnimationArray[MINUTES_IN_HOUR], MINUTES_IN_HOUR, au8CompressedArrayRingMiddle,
                            NOF_LEDS_MIDDLE_RING);

    // Send the compressed array full of animation to the Render Array Module
    LightEffects_RenderRings(au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRingOuter,
                             NOF_LEDS_OUTER_RING);
}