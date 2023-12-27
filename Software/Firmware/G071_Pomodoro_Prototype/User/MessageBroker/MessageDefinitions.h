#include "Common.h"
#include "MessageBroker.h"
#include "RealTimeClock_Datatypes.h"

typedef struct {
  uint8_t u8MinutesWorktimePeriod;
  uint8_t u8MinutesBreaktimePeriod;
} PomodoroPeriodConfiguration_t;