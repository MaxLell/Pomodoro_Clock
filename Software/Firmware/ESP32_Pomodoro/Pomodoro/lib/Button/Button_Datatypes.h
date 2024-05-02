#ifndef BUTTON_DATATYPES_H
#define BUTTON_DATATYPES_H

#include "Common.h"

typedef enum
{
    E_BTN_INVALID = 0U,
    E_BTN_TRIGGER,
    E_BTN_LAST
} ButtonTypes_e;

typedef enum
{
    E_BTN_EVENT_INVALID = 0U,
    E_BTN_EVENT_SHORT_PRESSED,
    E_BTN_EVENT_RELEASED,
    E_BTN_EVENT_LONG_PRESSED,
    E_BTN_EVENT_LAST
} ButtonEvent_e;

typedef struct
{
    u16 u16LongPressState;
    u32 u32State;
    bool bLongPressTriggered;
} DebounceFlags_s;

typedef struct
{
    DebounceFlags_s sDebounceFlags;
    ButtonTypes_e eButton;
    ButtonEvent_e eEvent;
} Button_s;

#endif // BUTTON_DATATYPES_H
