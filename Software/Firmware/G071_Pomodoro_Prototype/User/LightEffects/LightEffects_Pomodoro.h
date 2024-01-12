#ifndef LIGHTEFFECTS_POMODORO_H
#define LIGHTEFFECTS_POMODORO_H

#include "LightEffects.h"

/************************************************************
 * Public Data Structures for the Pomodoro
 ************************************************************/

#define MAX_SETTINGS 6U

typedef enum
{
    //       WT_BT
    E_EFFECT_25_5 = 0U,
    E_EFFECT_51_17,
    E_EFFECT_90_15,
    E_EFFECT_LAST
} LightEffect_Effect_e;

typedef enum
{
    E_PHASE_WORK_TIME = 0U,
    E_PHASE_BREAK_TIME,
    E_PHASE_NONE
} LightEffects_PomodoroPhase_e;

typedef enum
{
    E_MIDDLE_RING,
    E_OUTER_RING,
    E_INNER_RING,
    E_UNDEFINED_RING
} LightEffects_Ring_e;

typedef enum
{
    E_ANIMATION_OFF = 0U,
    E_ANIMATION_WORK_TIME,
    E_ANIMATION_BREAK_TIME,
    E_ANIMATION_BREAK_TIME_BRIGHT,
    E_ANIMATION_FLASHLIGHT,
    E_ANIMATION_NOT_DEFINED
} LightEffects_Animation_e;

typedef struct
{
    LightEffects_PomodoroPhase_e ePhase;
    LightEffects_Ring_e eRingType;
    LightEffects_Animation_e eAnimationType;
    uint8_t u8DuratationInMinutes;
    uint8_t u8MinuteOffset;
} LightEffects_PomodoroRingPhaseCfg_t;

/************************************************************
 * Public functions for the Pomodoro Sequence
 ************************************************************/

void LightEffects_getInitialPomodoroSetting(LightEffects_PomodoroRingPhaseCfg_t *out_sEffect,
                                            uint8_t *const inout_u8ArraySize, LightEffect_Effect_e in_eEffectType);

void LightEffects_isPhaseOver(const LightEffects_PomodoroRingPhaseCfg_t *const in_saEffect,
                              uint8_t in_u8EffectArraySize, BOOL *out_bWorktimeOver,
                              LightEffects_PomodoroPhase_e in_ePhase, LightEffects_Animation_e in_eAnimationType);

void LightEffects_updateWorktimeCfgForCurrentMinute(LightEffects_PomodoroRingPhaseCfg_t *const inout_asEffects,
                                                    uint8_t in_u8EffectArraySize,
                                                    LightEffects_PomodoroPhase_e in_ePhase);

void LightEffects_setAnimationInRingMinuteArray(uint8_t *out_au8RingArray, uint8_t u8ArraySize,
                                                uint8_t in_u8DurationInMinutes, uint8_t in_u8MinuteOffset,
                                                LightEffects_Animation_e eAnimation);

void LightEffects_AreThereActiveMinutesLeft(const LightEffects_PomodoroRingPhaseCfg_t *const in_sEffect,
                                            BOOL *out_bActiveMinutesLeft);

void LightEffects_getCompressedArraysForCurrentPhase(const LightEffects_PomodoroRingPhaseCfg_t *const in_asEffects,
                                                     uint8_t in_u8EffectArraySize,
                                                     LightEffects_PomodoroPhase_e in_ePhase,
                                                     uint8_t *out_MiddleRingCompressedArray,
                                                     uint8_t *out_OuterRingCompressedArray);

void LightEffects_RenderRingConfig(LightEffects_PomodoroRingPhaseCfg_t *const inout_psRingPhaseConfig,
                                   status_e *out_peRenderStatus);

#endif // LIGHTEFFECTS_POMODORO_H
