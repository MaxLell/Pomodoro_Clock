#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H
#include "Common.h"
#include "Config.h"

#define MINUTES_IN_HOUR 60

typedef enum
{
    LIGHTCONTROL_LED_OFF = 1U,
    LIGHTCONTROL_LED_RED = 5U,
    LIGHTCONTROL_LED_GREEN = 7U,
    LIGHTCONTROL_LED_BLUE = 9U,
} LightControl_Colors;

typedef enum
{
    LIGHTCONTROL_STATE_IDLE = 0U,
    LIGHTCONTROL_STATE_WORK = 1U,
    LIGHTCONTROL_STATE_BREAK = 2U,
} LightControl_States;

status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
                                             uint8_t in_u8WorktimeIntervalMin,
                                             uint8_t in_u8BreaktimeIntervalMin,
                                             uint8_t *inout_au8ColorArray);

status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                                  uint8_t in_u8CurrentMinute);

status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
                                          uint8_t *inout_au8LedToColorArray);

status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray);

status_t LightControl_init(uint8_t in_u8CurrentMinute);

status_t LightControl_endSequence(void);

status_t LightControl_runSequence(uint8_t in_u8CurrentMinute);

status_t LightControl_execute(uint8_t in_u8CurrentMinute);

status_t LightControl_sequenceIsCompleted(BOOL *out_bSequenceIsCompleted);

#endif // LIGHTCONTROL_H
