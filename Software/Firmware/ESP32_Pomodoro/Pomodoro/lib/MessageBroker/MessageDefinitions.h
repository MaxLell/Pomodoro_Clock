#ifndef MESSAGE_DEFINITIONS_H
#define MESSAGE_DEFINITIONS_H

#include "Common.h"
#include "MessageBroker.h"
#include "Button_Datatypes.h"

typedef struct
{
  bool bConfigWasUpdated;
  u8 u8MinutesWorktimePeriod;
  u8 u8MinutesBreaktimePeriod;
} PomodoroPeriodConfiguration_s;

typedef struct
{
  ButtonTypes_e eButton;
  ButtonEvent_e eEvent;
} ButtonMessage_s;

typedef struct
{
  u8 u8WorktimeMinutes;
  u8 u8BreaktimeMinutes;
} TimeCfg_s;

/*********************************************
 * Data structures for Tests
 *********************************************/

typedef struct
{
  u16 u16TimerPeriodMin;
  u16 u16TimerPeriodSec;
  u16 u16TimerPeriodSnoozeMs; // 5 Minute Snooze Interval (5000ms * 60 Increments = 5 Minutes) (for example)
  u16 u16TimerPeriodCancelSeqMs;
  u16 u16TimerPeriodWarningMs;
  u16 u16TimeOutPeriodMin;
} TestData_0004_s;

typedef struct
{
  u32 u32MinutePeriod;
  u32 u32WatchdogPeriod;
  u32 u32TimeoutPeriod;
} TestData_0006_s;

#endif // MESSAGE_DEFINITIONS_H
