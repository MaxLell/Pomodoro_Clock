#ifndef CONFIG_H
#define CONFIG_H
#include "Common.h"

#define TOTAL_LEDS_OUTER_RING 24
#define TOTAL_LEDS_MIDDLE_RING 16
#define TOTAL_LEDS_INNER_RING 8
#define TOTAL_LEDS (TOTAL_LEDS_OUTER_RING + TOTAL_LEDS_MIDDLE_RING + TOTAL_LEDS_INNER_RING)

#define MINUTES_IN_HOUR 60
#define TOTAL_MINUTES (MINUTES_IN_HOUR * 2)

#define MAX_POMODORO_SCORE 8

#define LED_BRIGHTNESS_HIGH 255
#define LED_BRIGHTNESS_MEDIUM 100
#define LED_BRIGHTNESS_LOW 10
#define LED_BRIGHTNESS_OFF 0

#define WS2812_HIGH_BIT 60
#define WS2812_LOW_BIT 30
#define WS2812_OFF 0
#define PWM_DATA_SIZE (24 * TOTAL_LEDS) + 50

status_t Config_setBreaktime(uint8_t in_u8BreaktimeIntervalMin);
status_t Config_getBreaktime(uint8_t *inout_u8BreaktimeIntervalMin);

status_t Config_setWorktime(uint8_t in_u8WorktimeIntervalMin);
status_t Config_getWorktime(uint8_t *inout_u8WorktimeIntervalMin);

#endif // CONFIG_H