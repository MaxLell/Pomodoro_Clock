#include "LightEffects.h"
#include "RgbLed_Config.h"
#include "mock_Delay.h"
#include "mock_RgbLed.h"
#include "unity.h"

/*********************************************
 * external static functions
 *********************************************/

/*********************************************
 * external static variables
 *********************************************/

/*********************************************
 * implementation
 *********************************************/

void setUp(void) {}

void tearDown(void) {}

/**
 * Helper functions
 * lubendu-function = <3
 */

void helper_printArray(uint8_t* in_au8Array, uint8_t in_u8ArraySize) {
  /**
   * This function prints the index of the array next to the value line by line
   * Example:
   * 0 - 0
   * 1 - 2
   * 2 - 2
   * 3 - 2
   * ...
   */
  for (uint8_t i = 0; i < in_u8ArraySize; i++) {
    if (i < 10) {
      printf("%d ---> %d\n", i, in_au8Array[i]);
    } else if ((i < 100) && (i >= 10)) {
      printf("%d --> %d\n", i, in_au8Array[i]);
    } else {
      printf("%d -> %d\n", i, in_au8Array[i]);
    }
  }
  printf("\n");
}

///////////////////////////////////////////////
// Data Structure Experiments
///////////////////////////////////////////////
void LightEffects_getInitialPomodoroSetting(
    LightEffects_PomodoroRingPhaseCfg_t* out_sEffect,
    uint8_t* const inout_u8ArraySize,
    LightEffect_Effect_e in_eEffectType) {
  {
    // Input Checks
    ASSERT_MSG(!(out_sEffect == NULL), "out_sEffect is NULL");
    ASSERT_MSG(!(inout_u8ArraySize == NULL), "inout_u8ArraySize is NULL");
    ASSERT_MSG(!(in_eEffectType >= E_EFFECT_LAST), "in_eEffectType is invalid");
  }

  switch (in_eEffectType) {
    case E_EFFECT_25_5: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 25;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 5;
      out_sEffect[u8idx].u8MinuteOffset = 25;
      u8idx++;
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 5;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      *inout_u8ArraySize = u8idx;
    } break;

    case E_EFFECT_51_17: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 51;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 17;
      out_sEffect[u8idx].u8MinuteOffset = 51;
      u8idx++;
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 17;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      *inout_u8ArraySize = u8idx;
    } break;

    case E_EFFECT_90_15: {
      uint8_t u8idx = 0;
      // Worktime
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_WORK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 30;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_WORK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 15;
      out_sEffect[u8idx].u8MinuteOffset = 30;
      u8idx++;
      // Breaktime
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_BREAK_TIME_BRIGHT;
      out_sEffect[u8idx].eRingType = E_INNER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 15;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      out_sEffect[u8idx].ePhase = E_PHASE_BREAK_TIME;
      out_sEffect[u8idx].eAnimationType = E_ANIMATION_FLASHLIGHT;
      out_sEffect[u8idx].eRingType = E_OUTER_RING;
      out_sEffect[u8idx].u8DuratationInMinutes = 59;
      out_sEffect[u8idx].u8MinuteOffset = 0;
      u8idx++;
      *inout_u8ArraySize = u8idx;
    } break;

    default:
      ASSERT_MSG(FALSE, "Unknown Effect");
      break;
  }
}
