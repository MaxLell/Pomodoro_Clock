#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

#include "PomodoroControl_Datatypes.h"

#include "CountdownTimer.h"
#include "Delay.h"
#include "RgbLed.h"
#include "RgbLed_Config.h"
#include "math.h"

#include "stdlib.h"

/************************************************************
 * Private Defines
 ************************************************************/

#define SEEKING_ATTENTION__MAX_BRIGHTNESS 200
#define SEEKING_ATTENTION__INCREMENT_REDUCER ((SEEKING_ATTENTION__MAX_BRIGHTNESS / 4) * 3) // 75% of the Max Brightness

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

void LightEffects_mapColorsToIdx(const LightEffects_Animation_e in_eAnimation, const uint8_t u8Idx)
{
    // Input Checks
    ASSERT_MSG(!(u8Idx >= RGB_LED_TOTAL_LEDS), "u8Idx is larger than RGB_LED_TOTAL_LEDS");
    ASSERT_MSG(!(in_eAnimation >= E_ANIMATION_NOT_DEFINED), "in_eAnimation is not defined");

    switch (in_eAnimation)
    {
        /**
         * Do not choose values below 3 for the LEDs, as they are not visible
         */
    case E_ANIMATION_OFF:
        RgbLed_setPixelColor(u8Idx, 0, 0, 0);
        break;
    case E_ANIMATION_WORK_TIME:
        RgbLed_setPixelColor(u8Idx, 50, 0, 0);
        break;
    case E_ANIMATION_BREAK_TIME:
        RgbLed_setPixelColor(u8Idx, 0, 50, 0);
        break;
    case E_ANIMATION_BREAK_TIME_BRIGHT:
        RgbLed_setPixelColor(u8Idx, 0, 100, 0);
        break;
    case E_ANIMATION_FLASHLIGHT:
        RgbLed_setPixelColor(u8Idx, 200, 200, 200);
        break;
    case E_ANIMATION_WARNING:
        RgbLed_setPixelColor(u8Idx, 50, 50, 0);
        break;
    case E_ANIMATION_CANCEL_SEQUENCE:
        RgbLed_setPixelColor(u8Idx, 100, 0, 200);
        break;
    case E_ANIMATION_SNOOZE:
        RgbLed_setPixelColor(u8Idx, 0, 0, 50);
        break;
    default:
        ASSERT_MSG(FALSE, "Unknown Animation Type");
        break;
    }
}

void LightEffects_RenderMiddleAndOuterRings(const uint8_t *const in_au8MiddleRingArray, uint8_t in_u8MiddleRingArraySize,
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
        LightEffects_mapColorsToIdx(in_au8OuterRingArray[i], u8LedIndex);
        u8LedIndex++;
    }

    uint8_t tmp = START_INDEX_MIDDLE_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    // Render the Middle ring
    for (uint8_t i = 0; i < in_u8MiddleRingArraySize; i++)
    {
        LightEffects_mapColorsToIdx(in_au8MiddleRingArray[i], u8LedIndex);
        u8LedIndex++;
    }

    tmp = START_INDEX_INNER_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    RgbLed_show();

    Delay_ms(10); // TODO: Fix the Bug, which makes it necessary to wait here
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

    Delay_ms(5); // TODO: Fix the Bug, which makes it necessary to wait here

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
    LightEffects_RenderMiddleAndOuterRings(au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRingOuter,
                                           NOF_LEDS_OUTER_RING);
}

void LightEffects_RenderRingCountdown(LightControl_RingCountdown_s *const psSelf)
{
    { // Input Checks
        ASSERT_MSG(!(psSelf == NULL), "psSelf is NULL");
    }

    // Generate the Minute Array for the Effect on the Inner Ring
    uint8_t au8MinuteArray[TOTAL_MINUTES] = {0};
    for (uint8_t i = MINUTES_IN_HOUR; i < (psSelf->u8CurrentFillingMin + MINUTES_IN_HOUR); i++)
    {
        au8MinuteArray[i] = psSelf->eEffect;
        switch (psSelf->eEffect)
        {
        case E_RING_COUNTDOWN_EFFECT__WARNING:
            au8MinuteArray[i] = E_ANIMATION_WARNING;
            break;

        case E_RING_COUNTDOWN_EFFECT__SNOOZE:
            au8MinuteArray[i] = E_ANIMATION_SNOOZE;
            break;

        case E_RING_COUNTDOWN_EFFECT__CANCEL_SEQ:
            au8MinuteArray[i] = E_ANIMATION_CANCEL_SEQUENCE;
            break;

        default:
            ASSERT_MSG(!(TRUE), "Unknown Animation Type");
            break;
        }
    }

    // Set all other entries to OFF
    // for (uint8_t i = 0; i < TOTAL_MINUTES; i++)
    // {
    //     if (!(au8MinuteArray[i] == psSelf->eEffect))
    //     {
    //         au8MinuteArray[i] = E_ANIMATION_OFF;
    //     }
    // }

    // Compress the array
    uint8_t au8CompressedArrayRingMiddle[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8CompressedArrayRingOuter[NOF_LEDS_OUTER_RING] = {0};
    LightEffects_scaleArray(au8MinuteArray, MINUTES_IN_HOUR, au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING);
    LightEffects_scaleArray(&au8MinuteArray[MINUTES_IN_HOUR], MINUTES_IN_HOUR, au8CompressedArrayRingOuter,
                            NOF_LEDS_OUTER_RING);

    // Send the compressed ful of the animation to the Render Array Module
    LightEffects_RenderMiddleAndOuterRings(au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRingOuter,
                                           NOF_LEDS_OUTER_RING);
}

void LightEffects_UpdateRingCountdown(LightControl_RingCountdown_s *const psSelf)
{
    { // Input Checks
        // Null Pointer Checks
        ASSERT_MSG(!(psSelf == NULL), "psSelf is NULL");
    }

    // update the filling counter
    if (psSelf->u8CurrentFillingMin > 0)
    {
        psSelf->u8CurrentFillingMin--;
    }
    else
    {
        // Set the complete flag if the filling counter is 0
        psSelf->bIsComplete = TRUE;
    }
}

void LightEffects_RenderSeekingAttention(LightEffects_SeekingAttention_s *const psSelf)
{
    // Input Argument Checks
    ASSERT_MSG(!(psSelf == NULL), "psSelf is NULL");

    if (FALSE == psSelf->bInitialized)
    {
        psSelf->bInitialized = TRUE;
        HelperFunction_getPseudoRandomNumber(START_INDEX_OUTER_RING, END_INDEX_MIDDLE_RING, (uint32_t *)&psSelf->u8CurrentLedIdx);
        psSelf->bSequenceComplete = 0;
        psSelf->bDecline = FALSE;
        psSelf->u8CurrentBrightness = 0;
    }

    if (FALSE == psSelf->bDecline)
    {
        if (psSelf->u8CurrentBrightness < SEEKING_ATTENTION__INCREMENT_REDUCER)
        {
            psSelf->u8CurrentBrightness += 3;
        }
        else if (psSelf->u8CurrentBrightness < SEEKING_ATTENTION__MAX_BRIGHTNESS)
        {
            psSelf->u8CurrentBrightness += 1;
        }
        else // (psSelf->u8CurrentBrightness >= SEEKING_ATTENTION__MAX_BRIGHTNESS)
        {
            psSelf->bDecline = TRUE;
        }

        RgbLed_setPixelColor(psSelf->u8CurrentLedIdx, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness);
    }

    if (TRUE == psSelf->bDecline)
    {
        if (psSelf->u8CurrentBrightness > 5)
        {
            psSelf->u8CurrentBrightness -= 1;
            RgbLed_setPixelColor(psSelf->u8CurrentLedIdx, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness);
            RgbLed_show();
        }
        else
        {
            psSelf->bSequenceComplete = TRUE;

            // Reset the state
            psSelf->bInitialized = FALSE;
            psSelf->bDecline = FALSE;
            psSelf->u8CurrentBrightness = 0;
            psSelf->u8CurrentLedIdx = 0;

            // Clear the LEDs
            LightEffects_ClearPomodoroProgressRings();
        }
    }
}

void LightEffects_RenderScore(uint32_t in_u32ScoreInMinutes)
{
    // Calculate the hours from the Minutes
    uint32_t u32Hours = in_u32ScoreInMinutes / MINUTES_IN_HOUR;

    // Make sure that the calculated Hours do not exceed 16h
    ASSERT_MSG(!(u32Hours > NOF_LEDS_INNER_RING), "u32Hours is larger than 12, which cannot be displayed on only one ring");

    for (uint32_t i = START_INDEX_INNER_RING; i < START_INDEX_INNER_RING + u32Hours; i++)
    {
        // Make sure that the index does not exceed the total number of LEDs of the Inner Ring
        ASSERT_MSG(!(i >= (START_INDEX_INNER_RING + NOF_LEDS_INNER_RING)), "i is larger than the total number of LEDs of the Inner Ring: %d", i);

        RgbLed_setPixelColor(i, 0, 0, 50);
    }

    RgbLed_show();
}

void LightEffects_ClearScore(void)
{
    for (uint32_t i = START_INDEX_INNER_RING; i < START_INDEX_INNER_RING + NOF_LEDS_INNER_RING; i++)
    {
        RgbLed_setPixelColor(i, 0, 0, 0);
    }
    RgbLed_show();
}