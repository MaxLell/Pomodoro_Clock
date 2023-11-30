/*
 * RgbLed.h
 *
 *  Created on: Nov 29, 2023
 *      Author: maxlell
 *
 * Source: https://controllerstech.com/interface-ws2812-with-stm32/
 * The solution created here is based on this information
 */

#ifndef RGBLED_H_
#define RGBLED_H_

#include "stdint.h"

#define RGB_LED_TOTAL_LEDS 24

void RgbLed_show(void);

void RgbLed_setPixelColor(
    uint8_t ledIndex,
    uint8_t u8Red, uint8_t u8Green, uint8_t u8Blue);

void RgbLed_isr();

void RgbLed_testDrawSpinningCircle();

#endif /* RGBLED_H_ */
