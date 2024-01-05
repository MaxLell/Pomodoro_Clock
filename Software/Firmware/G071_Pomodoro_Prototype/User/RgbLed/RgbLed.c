/*
 * RgbLed.c
 *
 *  Created on: Nov 29, 2023
 *      Author: maxlell
 */

#include "RgbLed.h"

#include "Common.h"
#include "Delay.h"
#include "main.h"
#include "tim.h"

#define BIT_WIDTH_RGB_LED 24
#define NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES 50
#define PWM_DATA_SIZE                        \
  (BIT_WIDTH_RGB_LED * RGB_LED_TOTAL_LEDS) + \
      NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES

#define WS2812B_HIGH_BIT 40
#define WS2812B_LOW_BIT 20
#define WS2812B_OFF 0

uint8_t bDataIsSent = 1;
uint16_t au16PwmData[PWM_DATA_SIZE];
uint8_t u8LedData[TOTAL_LEDS]
                 [4];  // This stores the u32Color data values of the LEDs

extern TIM_HandleTypeDef htim1;

void RgbLed_setPixelColor(uint8_t u8LedIdx,
                          uint8_t u8Red,
                          uint8_t u8Green,
                          uint8_t u8Blue) {
  { ASSERT_MSG(u8LedIdx < TOTAL_LEDS, "u8LedIdx out of bounds"); }

  u8LedData[u8LedIdx][0] = u8LedIdx;
  u8LedData[u8LedIdx][1] = u8Green;
  u8LedData[u8LedIdx][2] = u8Red;
  u8LedData[u8LedIdx][3] = u8Blue;
}

void RgbLed_show(void) {
  if (bDataIsSent == TRUE) {
    // What do you want from me compiler
    uint32_t u32LedPulses = 0;
    uint32_t u32Color;
    /**
     * PWM for LED Illumination
     */
    for (int k = 0; k < TOTAL_LEDS; k++) {
      u32Color = ((u8LedData[k][1] << 16) |  // green
                  (u8LedData[k][2] << 8) |   // red
                  (u8LedData[k][3]));        // blue

      /**
       * Parsing of the u32Color Array and inserting the respective PWM Value
       * For PWM generation
       */
      for (int8_t i = BIT_WIDTH_RGB_LED - 1; i >= 0; i--) {
        if (u32Color & (1 << i)) {
          au16PwmData[u32LedPulses] = WS2812B_HIGH_BIT;
        } else {
          au16PwmData[u32LedPulses] = WS2812B_LOW_BIT;
        }
        u32LedPulses++;
      }
    }

    /**
     * Insert some 0 values as a reset value to be placed in
     * between sequences
     */
    for (uint8_t i = 0; i < NUMBER_OF_OFF_PULSES_BETWEEN_LED_PULSES; i++) {
      au16PwmData[u32LedPulses] = WS2812B_OFF;
      u32LedPulses++;
    }

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)au16PwmData,
                          u32LedPulses);

    bDataIsSent = 0;
  }

  else {
    // YOUUUU DUU NUTHIN JUUHN SNUUW
  }
}

void RgbLed_isr() {
  /**
   * The DMA needs to be stopped, otherwise the signal
   * is repeated over and over again.
   * The problem remains, nonetheless: It takes the
   * ISR a couple of cycles to stop the TIM PWM
   * Therefore the TIM PWM continues to send out numbers
   *
   * This solution is not optimal, but functional, and
   * at the moment sufficient.
   */
  HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);

  bDataIsSent = 1;
}

/**
 * This is a test function, whose only purpose is to prove
 * the proper workings of the Rgb Led Ring.
 *
 * This function draws a light, that spins around the
 * RgbLed Circle
 */
void RgbLed_HardwareTest_DrawSpinningCircle() {
  uint8_t u8LedIndex = 0;
  for (uint8_t i = 0; i < 30; i++) {
    if (u8LedIndex == TOTAL_LEDS) {
      u8LedIndex = 0;
    }
    uint8_t effect[TOTAL_LEDS] = {2, 5, 5, 5, 2};

    uint8_t effect_size = sizeof(effect);
    for (uint8_t i = 0; i < TOTAL_LEDS; i++) {
      RgbLed_setPixelColor(i, 0, 0, 0);
    }
    for (uint8_t i = 0; i < effect_size; i++) {
      uint8_t tmp = (u8LedIndex + i) % TOTAL_LEDS;
      RgbLed_setPixelColor(tmp, effect[i], effect[i], effect[i]);
    }

    RgbLed_show();
    u8LedIndex++;

    HAL_Delay(30);
  }
}

void RgbLed_clear(void) {
  for (uint8_t i = 0; i < TOTAL_LEDS; i++) {
    RgbLed_setPixelColor(i, 0, 0, 0);
  }
  RgbLed_show();
}
