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

void LightEffects_scaleArray(const u8 *const in_au8SourceArray, u8 in_u8SourceArraySize,
                             u8 *out_au8TargetArray, u8 in_u8TargetArraySize)
{
    { // Input Checks
        ASSERT_MSG(!(in_au8SourceArray == NULL), "in_au8SourceArray is NULL Ptr");
        ASSERT_MSG(!(out_au8TargetArray == NULL), "in_au8SourceArray is NULL Ptr");
        ASSERT_MSG(!(in_u8SourceArraySize == 0), "Provided in_u8SourceArraySize needs to be larger then 0");
        ASSERT_MSG(!(in_u8TargetArraySize == 0), "Provided in_u8TargetArraySize needs to be larger then 0");
    }

    // Calculate the Scale Factor
    f32 fScaleFactor = (f32)in_u8SourceArraySize / (f32)in_u8TargetArraySize;

    // Scale the Array
    for (u8 i = 0; i < in_u8TargetArraySize; i++)
    {
        out_au8TargetArray[i] = in_au8SourceArray[(u8)(i * fScaleFactor)];
    }
}
void LightEffects_DotAroundTheCircle(status_e *out_eSequenceStatus, u16 u16PeriodPerIncrementMs)
{
    {
        // Input Checks
        ASSERT_MSG(!(NULL == out_eSequenceStatus), "Sequence Status cannot be NULL");
        ASSERT_MSG(!(u16PeriodPerIncrementMs == 0U), "Period cannot be 0");
    }
    // Variable Declarations
    static u8 u8LedIndex = 0;
    u8 effect[TOTAL_LEDS] = {2, 5, 5, 5, 2};
    u8 effect_size = sizeof(effect);

    // Increment the ledIndex
    u8LedIndex++;

    if (u8LedIndex == TOTAL_LEDS)
    {
        // Set the sequence status to complete
        *out_eSequenceStatus = STATUS_IN_PROGRESS;

        // Reset the ledIndex
        u8LedIndex = 0;

        // Disable all LEDs
        RgbLed_clear();
    }
    else
    {
        for (u8 i = 0; i < TOTAL_LEDS; i++)
        {
            RgbLed_setPixelColor(i, 0, 0, 0);
        }

        for (u8 i = 0; i < effect_size; i++)
        {
            u8 tmp = (u8LedIndex + i) % TOTAL_LEDS;
            RgbLed_setPixelColor(tmp, effect[i], effect[i], effect[i]);
        }

        // Set the Sequence Status to in progress
        *out_eSequenceStatus = STATUS_IN_PROGRESS;
    }
    // Wait a fixed delay
    Delay_ms(u16PeriodPerIncrementMs);

    // Show the sequence on the LEDs
    RgbLed_show();
}

void LightEffects_ClearAllRingLeds(void)
{
    RgbLed_clear();
}

/************************************************************
 * Implementation for the Pomodoro
 ************************************************************/

void LightEffects_mapColorsToIdx(const LightEffects_Animation_e in_eAnimation, const u8 u8Idx)
{
    // Input Checks
    ASSERT_MSG(!(u8Idx >= TOTAL_LEDS), "u8Idx is larger than TOTAL_LEDS");
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
        RgbLed_setPixelColor(u8Idx, 30, 0, 0);
        break;
    case E_ANIMATION_BREAK_TIME:
        RgbLed_setPixelColor(u8Idx, 0, 30, 0);
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
        ASSERT_MSG(false, "Unknown Animation Type");
        break;
    }
}

void LightEffects_RenderMiddleAndOuterRings(const u8 *const in_au8MiddleRingArray, u8 in_u8MiddleRingArraySize,
                                            const u8 *const in_au8OuterRingArray, u8 in_u8OuterRingArraySize)
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
    u8 u8LedIndex = START_INDEX_OUTER_RING;
    for (u8 i = 0; i < in_u8OuterRingArraySize; i++)
    {
        LightEffects_mapColorsToIdx(in_au8OuterRingArray[i], u8LedIndex);
        u8LedIndex++;
    }

    u8 tmp = START_INDEX_MIDDLE_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    // Render the Middle ring
    for (u8 i = 0; i < in_u8MiddleRingArraySize; i++)
    {
        LightEffects_mapColorsToIdx(in_au8MiddleRingArray[i], u8LedIndex);
        u8LedIndex++;
    }

    tmp = START_INDEX_INNER_RING;
    ASSERT_MSG(!(u8LedIndex != tmp), "u8LedIndex is not equal to %d. It is instead %d", tmp, u8LedIndex);

    RgbLed_show();
}

void LightEffects_ClearPomodoroProgressRings(void)
{
    // Clear the LEDs of the OUTER RING
    u8 u8LedIndex = START_INDEX_OUTER_RING;
    for (u8 i = 0; i < NOF_LEDS_OUTER_RING; i++)
    {
        RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
        u8LedIndex++;
    }

    ASSERT_MSG(!(u8LedIndex != START_INDEX_MIDDLE_RING), "u8LedIndex is not equal to %d. It is instead %d",
               START_INDEX_MIDDLE_RING, u8LedIndex);

    // Clear the LEDs of the MIDDLE RING
    u8LedIndex = START_INDEX_MIDDLE_RING;
    for (u8 i = 0; i < NOF_LEDS_MIDDLE_RING; i++)
    {
        RgbLed_setPixelColor(u8LedIndex, 0, 0, 0);
        u8LedIndex++;
    }

    RgbLed_show();
    ASSERT_MSG(!(u8LedIndex != START_INDEX_INNER_RING), "u8LedIndex is not equal to %d. It is instead %d",
               START_INDEX_INNER_RING, u8LedIndex);
}

void LightEffects_RenderPomodoro(const u8 *const in_au8MinuteArray, const u8 in_u8ArraySize,
                                 bool bIsWorktimeOver)
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

    /**
     * Use a toggle timer to toggle the BreakTime Animation on and off
     */
    static bool bRunOnce = true;
    static CountdownTimer_t sToggleTimer = {0};
    if (bRunOnce)
    {
        Countdown_initTimerMs(&sToggleTimer, 100, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_startTimer(&sToggleTimer);
        bRunOnce = false;
    }

    // Create a Minute Array filled with the animation types
    u8 au8AnimationArray[TOTAL_MINUTES] = {0};

    for (u8 i = 0; i < in_u8ArraySize; i++)
    {
        switch (in_au8MinuteArray[i])
        {
        case E_CFG_WORKTIME:
            au8AnimationArray[i] = E_ANIMATION_WORK_TIME;
            ASSERT_MSG(!(true == bIsWorktimeOver),
                       "Worktime is over - there should be no entires with Worktime in the Minute Array");
            break;

        case E_CFG_BREAKTIME:

            au8AnimationArray[i] = bIsWorktimeOver ? E_ANIMATION_BREAK_TIME_BRIGHT : E_ANIMATION_BREAK_TIME;

            break;

        case E_CFG_OFF:
            au8AnimationArray[i] = E_ANIMATION_OFF;
            break;

        default:
            ASSERT_MSG(false, "Unknown Animation Type");
            break;
        }
    }

    // if the Worktime is over, set the animation to flashlight on the inner ring
    if (bIsWorktimeOver)
    {
        static bool bToggle = false;
        if (Countdown_getTimerStatus(&sToggleTimer) == E_COUNTDOWN_TIMER_EXPIRED)
        {
            bToggle = !bToggle;
        }

        for (u8 i = MINUTES_IN_HOUR; i < TOTAL_MINUTES; i++)
        {
            if (bToggle)
            {
                au8AnimationArray[i] = E_ANIMATION_FLASHLIGHT;
            }
            else
            {
                au8AnimationArray[i] = E_ANIMATION_OFF;
            }
        }
    }

    // Compress the Array
    u8 au8CompressedArrayRingOuter[NOF_LEDS_OUTER_RING] = {0};
    u8 au8CompressedArrayRingMiddle[NOF_LEDS_MIDDLE_RING] = {0};
    LightEffects_scaleArray(au8AnimationArray, MINUTES_IN_HOUR, au8CompressedArrayRingOuter, NOF_LEDS_OUTER_RING);
    LightEffects_scaleArray(&au8AnimationArray[MINUTES_IN_HOUR], MINUTES_IN_HOUR, au8CompressedArrayRingMiddle,
                            NOF_LEDS_MIDDLE_RING);

    // Send the compressed array full of animation to the Render Array Module
    LightEffects_RenderMiddleAndOuterRings(au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRingOuter,
                                           NOF_LEDS_OUTER_RING);
}

void LightEffects_RenderRingCountdown(LightEffects_RingCountdown_s *const psSelf)
{
    { // Input Checks
        ASSERT_MSG(!(psSelf == NULL), "psSelf is NULL");
    }

    // Generate the Minute Array for the Effect on the Inner Ring
    u8 au8MinuteArray[TOTAL_MINUTES] = {0};
    for (u8 i = MINUTES_IN_HOUR; i < (psSelf->u8CurrentFillingMin + MINUTES_IN_HOUR); i++)
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
            ASSERT_MSG(!(true), "Unknown Animation Type");
            break;
        }
    }

    // Compress the array
    u8 au8CompressedArrayRingMiddle[NOF_LEDS_MIDDLE_RING] = {0};
    u8 au8CompressedArrayRingOuter[NOF_LEDS_OUTER_RING] = {0};
    LightEffects_scaleArray(au8MinuteArray, MINUTES_IN_HOUR, au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING);
    LightEffects_scaleArray(&au8MinuteArray[MINUTES_IN_HOUR], MINUTES_IN_HOUR, au8CompressedArrayRingOuter,
                            NOF_LEDS_OUTER_RING);

    // Send the compressed ful of the animation to the Render Array Module
    LightEffects_RenderMiddleAndOuterRings(au8CompressedArrayRingMiddle, NOF_LEDS_MIDDLE_RING, au8CompressedArrayRingOuter,
                                           NOF_LEDS_OUTER_RING);
}

void LightEffects_UpdateRingCountdown(LightEffects_RingCountdown_s *const psSelf)
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
        psSelf->bIsComplete = true;
    }
}

void LightEffects_RenderSeekingAttention(LightEffects_SeekingAttention_s *const psSelf)
{
    // Input Argument Checks
    ASSERT_MSG(!(psSelf == NULL), "psSelf is NULL");

    if (false == psSelf->bInitialized)
    {
        psSelf->bInitialized = true;
        HelperFunction_getPseudoRandomNumber(START_INDEX_OUTER_RING, END_INDEX_MIDDLE_RING, (uint32_t *)&psSelf->u8CurrentLedIdx);
        psSelf->bSequenceComplete = 0;
        psSelf->bDecline = false;
        psSelf->u8CurrentBrightness = 0;
    }

    if (false == psSelf->bDecline)
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
            psSelf->bDecline = true;
        }

        RgbLed_setPixelColor(psSelf->u8CurrentLedIdx, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness);
    }

    if (true == psSelf->bDecline)
    {
        if (psSelf->u8CurrentBrightness > 5)
        {
            psSelf->u8CurrentBrightness -= 1;
            RgbLed_setPixelColor(psSelf->u8CurrentLedIdx, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness, psSelf->u8CurrentBrightness);
            RgbLed_show();
        }
        else
        {
            psSelf->bSequenceComplete = true;

            // Reset the state
            psSelf->bInitialized = false;
            psSelf->bDecline = false;
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

    // when you work more then 12h - then it is capped at 12h, so that the LEDs are not overfilled
    if (u32Hours <= NOF_LEDS_INNER_RING)
    {
        for (uint32_t i = START_INDEX_INNER_RING; i < START_INDEX_INNER_RING + u32Hours; i++)
        {
            RgbLed_setPixelColor(i, 0, 0, 50);
        }
    }
    else
    {
        for (uint32_t i = START_INDEX_INNER_RING; i < START_INDEX_INNER_RING + NOF_LEDS_INNER_RING; i++)
        {
            RgbLed_setPixelColor(i, 0, 0, 50);
        }
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
