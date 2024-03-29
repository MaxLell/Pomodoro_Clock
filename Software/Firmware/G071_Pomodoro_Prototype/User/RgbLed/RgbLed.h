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

#include "Common.h"
#include "RgbLed_Config.h"

void RgbLed_show(void);

void RgbLed_setPixelColor(uint8_t ledIndex,
                          uint8_t u8Red,
                          uint8_t u8Green,
                          uint8_t u8Blue);

void RgbLed_isr();

void RgbLed_clear(void);

void RgbLed_HardwareTest_DrawSpinningCircle();

#endif /* RGBLED_H_ */
