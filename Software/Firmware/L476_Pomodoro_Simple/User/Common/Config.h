#ifndef CONFIG_H
#define CONFIG_H
#include "Common.h"

#define TOTAL_LEDS_OUTER_RING 24
#define TOTAL_LEDS_MIDDLE_RING 16
#define TOTAL_LEDS_INNER_RING 8
#define TOTAL_LEDS (TOTAL_LEDS_OUTER_RING + TOTAL_LEDS_MIDDLE_RING + TOTAL_LEDS_INNER_RING)

#define MINUTES_IN_HOUR 60
#define TOTAL_MINUTES (MINUTES_IN_HOUR * 2)

status_t Config_setBreaktime(uint8_t in_u8BreaktimeIntervalMin);
status_t Config_getBreaktime(uint8_t *inout_u8BreaktimeIntervalMin);

status_t Config_setWorktime(uint8_t in_u8WorktimeIntervalMin);
status_t Config_getWorktime(uint8_t *inout_u8WorktimeIntervalMin);

#endif // CONFIG_H