#include "Common.h"
#include "MessageBroker.h"
#include "RealTimeClock_Datatypes.h"

typedef struct {
  uint8_t u8WorktimePeriodMin;
  uint8_t u8BreaktimePeriodMin;
} PomodoroPeriodConfiguration_t;