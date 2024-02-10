#ifndef MESSAGE_DEFINITIONS_H
#define MESSAGE_DEFINITIONS_H

#include "Common.h"
#include "MessageBroker.h"
#include "Button_Datatypes.h"

typedef struct  {
  uint8_t u8MinutesWorktimePeriod;
  uint8_t u8MinutesBreaktimePeriod;
} PomodoroPeriodConfiguration_t;

typedef struct {
  ButtonTypes_e eButton;
  Event_e eEvent;
}ButtonMessage_s;

#endif  // MESSAGE_DEFINITIONS_H
