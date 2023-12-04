#include "CountdownTimer_Hardware.h"

#include "main.h"
void CountdownTimer_Hardware_getSysTickCount(uint32_t *out_u32SysTickCount) {
  {  // Input Checks
    ASSERT_MSG(!(NULL == out_u32SysTickCount),
               "out_u32SysTickCount cannot be NULL");
  }
  *out_u32SysTickCount = HAL_GetTick();
}