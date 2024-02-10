#ifndef BUTTON_DATATYPES_H
#define BUTTON_DATATYPES_H

#include "Common.h"

typedef enum {
    E_BUTTON_INVALID = 0U,
    E_BUTTON_TRIGGER,
    E_BUTTON_ENCODER,
    E_BUTTON_SHOULDER_LEFT,
    E_BUTTON_SHOULDER_RIGHT,
    E_BUTTON_LAST
} ButtonTypes_e;

typedef enum {
    E_BTN_EVENT_INVALID = 0U,
    E_BTN_EVENT_SHORT_PRESSED,
    E_BTN_EVENT_RELEASED,
    E_BTN_EVENT_LONG_PRESSED,
    E_BTN_EVENT_LAST
} Event_e;

typedef struct {
    uint16_t u16LongPressState;
    uint32_t u32State;
    BOOL bLongPressTriggered;
} DebounceFlags_s;

typedef struct {
    DebounceFlags_s sDebounceFlags;
    ButtonTypes_e eButton;
    Event_e eEvent;
} Button_s;

#endif // BUTTON_DATATYPES_H
