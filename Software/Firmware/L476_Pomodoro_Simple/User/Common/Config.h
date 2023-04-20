#ifndef CONFIG_H
#define CONFIG_H
#include "Common.h"

#define TOTAL_LEDS 24
#define TOTAL_LEDS_OUTER_RING 24
#define TOTAL_LEDS_INNER_RING 0

status_t Config_setBreaktime(uint8_t in_u8BreaktimeIntervalMin);
status_t Config_getBreaktime(uint8_t *inout_u8BreaktimeIntervalMin);

status_t Config_setWorktime(uint8_t in_u8WorktimeIntervalMin);
status_t Config_getWorktime(uint8_t *inout_u8WorktimeIntervalMin);

#endif // CONFIG_H