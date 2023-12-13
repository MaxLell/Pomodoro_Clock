#ifndef REALTIMECLOCK_DATATYPES_H
#define REALTIMECLOCK_DATATYPES_H

#include "Common.h"

// Enum for the days of the week
typedef enum {
  E_RTC_DAY_MONDAY = 1U,
  E_RTC_DAY_TUESDAY,
  E_RTC_DAY_WEDNESDAY,
  E_RTC_DAY_THURSDAY,
  E_RTC_DAY_FRIDAY,
  E_RTC_DAY_SATURDAY,
  E_RTC_DAY_SUNDAY,
} RealTimeClock_Days_e;

typedef struct {
  uint8_t u8Hour;
  uint8_t u8Minute;
  uint8_t u8Second;
  uint8_t u8Day;
  uint8_t u8Month;
  uint8_t u8Year;
} TimeAndDate_t;

#endif  // REALTIMECLOCK_DATATYPES_H
