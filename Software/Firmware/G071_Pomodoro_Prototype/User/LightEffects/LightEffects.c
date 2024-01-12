#include "LightEffects.h"
#include "LightEffects_Pomodoro.h"

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

void LightEffects_isPhaseOver(const LightEffects_PomodoroRingPhaseCfg_t *const in_saEffect,
                              uint8_t in_u8EffectArraySize, BOOL *out_bPhaseOver,
                              LightEffects_PomodoroPhase_e in_ePhase, LightEffects_Animation_e in_eAnimationType)
{
    { // Input Checks
        ASSERT_MSG(!(in_saEffect == NULL), "in_saEffect is NULL");
        ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
        ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS), "in_u8EffectArraySize is larger then MAX_SETTINGS");
        ASSERT_MSG(!(out_bPhaseOver == NULL), "out_bPhaseOver is NULL");
        ASSERT_MSG(!(in_eAnimationType >= E_ANIMATION_NOT_DEFINED),
                   "in_eAnimationType is larger then E_ANIMATION_NOT_DEFINED");
    }
    BOOL tmp = TRUE;
    for (uint8_t i = 0; i < in_u8EffectArraySize; i++)
    {
        if (in_saEffect[i].ePhase == in_ePhase)
        {
            if (in_saEffect[i].eAnimationType == in_eAnimationType)
            {
                if (in_saEffect[i].u8DuratationInMinutes != 0)
                {
                    tmp = FALSE;
                    break;
                }
            }
        }
    }
    *out_bPhaseOver = tmp;
}

void LightEffects_getCompressedArraysForCurrentPhase(const LightEffects_PomodoroRingPhaseCfg_t *const in_asEffects,
                                                     uint8_t in_u8EffectArraySize,
                                                     LightEffects_PomodoroPhase_e in_ePhase,
                                                     uint8_t *out_MiddleRingCompressedArray,
                                                     uint8_t *out_OuterRingCompressedArray)
{
    { // Input Checks
        ASSERT_MSG(!(in_asEffects == NULL), "in_asEffects is NULL");
        ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
        ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS), "in_u8EffectArraySize is larger then MAX_SETTINGS");
        ASSERT_MSG(!(in_ePhase > E_PHASE_BREAK_TIME), "in_ePhase is larger then E_PHASE_BREAK_TIME");
        ASSERT_MSG(!(out_MiddleRingCompressedArray == NULL), "out_MiddleRingCompressedArray is NULL");
        ASSERT_MSG(!(out_OuterRingCompressedArray == NULL), "out_OuterRingCompressedArray is NULL");
    }

    uint8_t au8MiddleRingMinuteArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8OuterRingMinuteArray[MINUTES_IN_HOUR] = {0};

    for (uint8_t i = 0; i < in_u8EffectArraySize; i++)
    {
        if (in_asEffects[i].ePhase == in_ePhase)
        {
            if (in_asEffects[i].eRingType == E_MIDDLE_RING)
            {
                LightEffects_setAnimationInRingMinuteArray(
                    au8MiddleRingMinuteArray, MINUTES_IN_HOUR, in_asEffects[i].u8DuratationInMinutes,
                    in_asEffects[i].u8MinuteOffset, in_asEffects[i].eAnimationType);
            }
            else if (in_asEffects[i].eRingType == E_OUTER_RING)
            {
                LightEffects_setAnimationInRingMinuteArray(
                    au8OuterRingMinuteArray, MINUTES_IN_HOUR, in_asEffects[i].u8DuratationInMinutes,
                    in_asEffects[i].u8MinuteOffset, in_asEffects[i].eAnimationType);
            }
            else
            {
                ASSERT_MSG(FALSE, "Unknown Ring Type: %d", in_asEffects[i].eRingType);
            }
        }
    }

    uint8_t au8MiddleRingCompressedArray[NOF_LEDS_MIDDLE_RING] = {0};
    uint8_t au8OuterRingCompressedArray[NOF_LEDS_OUTER_RING] = {0};

    LightEffects_scaleArray(au8MiddleRingMinuteArray, MINUTES_IN_HOUR, au8MiddleRingCompressedArray,
                            NOF_LEDS_MIDDLE_RING);
    LightEffects_scaleArray(au8OuterRingMinuteArray, MINUTES_IN_HOUR, au8OuterRingCompressedArray, NOF_LEDS_OUTER_RING);

    // Copy the Compressed Array to the Output
    for (uint8_t i = 0; i < NOF_LEDS_MIDDLE_RING; i++)
    {
        out_MiddleRingCompressedArray[i] = au8MiddleRingCompressedArray[i];
    }
    for (uint8_t i = 0; i < NOF_LEDS_OUTER_RING; i++)
    {
        out_OuterRingCompressedArray[i] = au8OuterRingCompressedArray[i];
    }
}

void LightEffects_setAnimationInRingMinuteArray(uint8_t *out_au8RingArray, uint8_t u8ArraySize,
                                                uint8_t in_u8DurationInMinutes, uint8_t in_u8MinuteOffset,
                                                LightEffects_Animation_e eAnimation)
{
    { // input Checks
        // Make sure that the array size is exactly Max Minutes in an hour
        ASSERT_MSG(!(u8ArraySize != MINUTES_IN_HOUR), "u8ArraySize is not equal to MINUTES_IN_HOUR");

        // Make sure that none of the existing entries within the provided array
        // exceed the range of animation enums
        for (uint8_t i = 0; i < u8ArraySize; i++)
        {
            ASSERT_MSG(!(out_au8RingArray[i] > E_ANIMATION_NOT_DEFINED),
                       "out_au8RingArray[i] is larger then E_ANIMATION_NOT_DEFINED %d", out_au8RingArray[i]);
        }

        // Make sure that the provided Minutes do not exceed the Max Minutes in an
        // hour
        ASSERT_MSG(!(in_u8DurationInMinutes > MINUTES_IN_HOUR),
                   "in_u8DurationInMinutes is larger then MINUTES_IN_HOUR");

        // Make sure that the offset is does not exceed the Max Minutes in an hour
        ASSERT_MSG(!(in_u8MinuteOffset > MINUTES_IN_HOUR), "in_u8MinuteOffset is larger then MINUTES_IN_HOUR");

        // Run Null Pointer Checks
        ASSERT_MSG(!(out_au8RingArray == NULL), "out_au8RingArray is NULL");

        // Make sure that the animation is within bounds
        ASSERT_MSG(!(eAnimation >= E_ANIMATION_NOT_DEFINED), "eAnimation is larger then E_ANIMATION_NOT_DEFINED");
    }

    uint8_t idx = in_u8MinuteOffset;
    // Inset the current Animation
    for (uint8_t i = 0; i < in_u8DurationInMinutes; i++)
    {
        if (idx > (MINUTES_IN_HOUR - 1))
        {
            idx = 0;
        }
        // Make sure that previous Entries are not overwritten
        ASSERT_MSG(!(E_ANIMATION_OFF != out_au8RingArray[idx]), "Animation overwritten at idx %d", idx);
        out_au8RingArray[idx] = eAnimation;
        idx++;
    }
}

void LightEffects_updateWorktimeCfgForCurrentMinute(LightEffects_PomodoroRingPhaseCfg_t *const inout_asEffects,
                                                    uint8_t in_u8EffectArraySize,
                                                    LightEffects_PomodoroPhase_e in_ePhase)
{
    { // Input Checks
        ASSERT_MSG(!(inout_asEffects == NULL), "inout_asEffects is NULL");
        ASSERT_MSG(!(in_u8EffectArraySize == 0), "in_u8EffectArraySize is 0");
        ASSERT_MSG(!(in_u8EffectArraySize > MAX_SETTINGS), "in_u8EffectArraySize is larger then MAX_SETTINGS");
    }

    for (uint8_t i = 0; i < in_u8EffectArraySize; i++)
    {
        // Only process the entries for the current phase
        if (inout_asEffects[i].ePhase == in_ePhase)
        {
            // Only process cfgs which still have active Minutes left otherwise skip
            BOOL bActiveMinutesLeft;
            LightEffects_AreThereActiveMinutesLeft(&inout_asEffects[i], &bActiveMinutesLeft);
            if (bActiveMinutesLeft == FALSE)
            {
                continue;
            }
            inout_asEffects[i].u8DuratationInMinutes -= 1;
            inout_asEffects[i].u8MinuteOffset += 1;

            // Only process the first element (The inner Ring)
            break;
        }
    }
}

void LightEffects_AreThereActiveMinutesLeft(const LightEffects_PomodoroRingPhaseCfg_t *const in_sEffect,
                                            BOOL *out_bActiveMinutesLeft)
{
    { // Input Checks
        ASSERT_MSG(!(in_sEffect == NULL), "in_sEffect is NULL");
        ASSERT_MSG(!(out_bActiveMinutesLeft == NULL), "out_bActiveMinutesLeft is NULL");
    }
    *out_bActiveMinutesLeft = (in_sEffect->u8DuratationInMinutes != 0) ? TRUE : FALSE;
}

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

void LightEffects_getInitialPomodoroSetting(LightEffects_PomodoroRingPhaseCfg_t *out_sEffect,
                                            uint8_t *const inout_u8ArraySize,
                                            LightEffect_PomodoroConfig_e in_eEffectType)
{
    {
        // Input Checks
        ASSERT_MSG(!(out_sEffect == NULL), "out_sEffect is NULL");
        ASSERT_MSG(!(inout_u8ArraySize == NULL), "inout_u8ArraySize is NULL");
        ASSERT_MSG(!(in_eEffectType >= E_EFFECT_LAST), "in_eEffectType is invalid");
        ASSERT_MSG(!(in_eEffectType <= E_EFFECT_FIRST), "in_eEffectType needs to be initialized");
    }

    switch (in_eEffectType)
    {
    case E_EFFECT_25_5: {
        uint8_t u8idx = 0;
        // Worktime
        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 25;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 5;
        out_sEffect[u8idx].u8MinuteOffset = 25;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        // Warning
        out_sEffect[u8idx].ePhase = E_PHASE_WARNING;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WARNING;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        // Breaktime
        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 5;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        *inout_u8ArraySize = u8idx;
    }
    break;

    case E_EFFECT_51_17: {
        uint8_t u8idx = 0;
        // Worktime
        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 51;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 17;
        out_sEffect[u8idx].u8MinuteOffset = 51;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        // Warning
        out_sEffect[u8idx].ePhase = E_PHASE_WARNING;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WARNING;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        // Breaktime
        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 17;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        *inout_u8ArraySize = u8idx;
    }
    break;

    case E_EFFECT_90_15: {
        uint8_t u8idx = 0;
        // Worktime
        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 30;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 15;
        out_sEffect[u8idx].u8MinuteOffset = 30;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        // Warning
        out_sEffect[u8idx].ePhase = E_PHASE_WARNING;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_WARNING;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        // Breaktime
        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
        out_sEffect[u8idx].eRingType = E_OUTER_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 15;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");

        out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
        out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
        out_sEffect[u8idx].eRingType = E_MIDDLE_RING;
        out_sEffect[u8idx].u8DuratationInMinutes = 59;
        out_sEffect[u8idx].u8MinuteOffset = 0;
        u8idx++;
        ASSERT_MSG(!(u8idx > MAX_SETTINGS), "u8idx is larger then MAX_SETTINGS");
        *inout_u8ArraySize = u8idx;
    }
    break;

    default:
        ASSERT_MSG(FALSE, "Unknown Effect");
        break;
    }
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