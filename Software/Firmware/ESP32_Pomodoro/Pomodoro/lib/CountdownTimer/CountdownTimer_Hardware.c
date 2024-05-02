#include "CountdownTimer_Hardware.h"
#include "Arduino.h"

void CountdownTimer_Hardware_getTickCount(u32 *out_u32TickCount)
{
  { // Input Checks
    ASSERT_MSG(!(NULL == out_u32TickCount),
               "out_u32TickCount cannot be NULL");
  }
  TickType_t xTickCount = xTaskGetTickCount();

  *out_u32TickCount = xTickCount;
}