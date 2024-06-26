#ifndef MESSAGE_DEFINITIONS_H
#define MESSAGE_DEFINITIONS_H

#include "Common.h"
#include "MessageBroker.h"
#include "Button_Datatypes.h"

typedef struct
{
  BOOL bConfigWasUpdated;
  uint8_t u8MinutesWorktimePeriod;
  uint8_t u8MinutesBreaktimePeriod;
} PomodoroPeriodConfiguration_s;

typedef struct
{
  ButtonTypes_e eButton;
  Event_e eEvent;
} ButtonMessage_s;

typedef struct
{
  uint8_t u8WorktimeMinutes;
  uint8_t u8BreaktimeMinutes;
} TimeCfg_s;

/*********************************************
 * Data structures for Tests
 *********************************************/

typedef struct
{
  uint16_t u16TimerPeriodMin;
  uint16_t u16TimerPeriodSec;
  uint16_t u16TimerPeriodSnoozeMs; // 5 Minute Snooze Interval (5000ms * 60 Increments = 5 Minutes) (for example)
  uint16_t u16TimerPeriodCancelSeqMs;
  uint16_t u16TimerPeriodWarningMs;
  uint16_t u16TimeOutPeriodMin;
} TestData_0004_s;

typedef struct
{
  uint32_t u32MinutePeriod;
  uint32_t u32WatchdogPeriod;
  uint32_t u32TimeoutPeriod;
} TestData_0006_s;

#endif // MESSAGE_DEFINITIONS_H
