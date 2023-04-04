#ifndef CONFIG_H
#define CONFIG_H
#include "Common.h"

#define TOTAL_LEDS 24

uint8_t Config_setBreaktime(uint8_t in_u8BreaktimeIntervalMin);
uint8_t Config_getBreaktime(uint8_t *inout_u8BreaktimeIntervalMin);

uint8_t Config_setWorktime(uint8_t in_u8WorktimeIntervalMin);
uint8_t Config_getWorktime(uint8_t *inout_u8WorktimeIntervalMin);

#endif // CONFIG_H