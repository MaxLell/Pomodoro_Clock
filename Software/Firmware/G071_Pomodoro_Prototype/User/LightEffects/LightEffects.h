/**
 * @file LightEffects.h
 * @brief LightEffects library contains all the different light effects
 *        that can be displayed on the LED strip.
 * It basically contains 2 light effects:
 * - The Seeking Attention effect which is used to attract the user's attention
 * - The Pomodoro Sequence effect which is used to display the current pomodoro
 * @author Maximilian Lell (maximilian.lell@gmail.com)
 */

#ifndef LIGHTEFFECTS_H
#define LIGHTEFFECTS_H

#include "Common.h"

void LightEffects_init();

status_t LightEffects_execute();

#endif // LIGHTEFFECTS_H
