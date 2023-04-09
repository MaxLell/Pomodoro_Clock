#include "User/Common/Config.h"
#include "User/Common/Common.h"










typedef enum

{

    E_LCTRL_STATE_IDLE = 0U,

    E_LCTRL_STATE_WORKTIME,

    E_LCTRL_STATE_BREAKTIME,

} LightControl_States;



typedef enum

{

    LIGHTCONTROL_LED_OFF = 1U,

    LIGHTCONTROL_LED_RED = 5U,

    LIGHTCONTROL_LED_GREEN = 7U,

    LIGHTCONTROL_LED_BLUE = 9U,

} LightControl_Colors;



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
