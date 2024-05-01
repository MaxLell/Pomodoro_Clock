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

#ifdef __cplusplus
extern "C"
{
#endif

    void RgbLed_init(void);

    void RgbLed_setPixelColor(u8 ledIndex,
                              u8 u8Red,
                              u8 u8Green,
                              u8 u8Blue);

    void RgbLed_show(void);

    void RgbLed_clear(void);

#ifdef __cplusplus
}
#endif

#endif /* RGBLED_H_ */
