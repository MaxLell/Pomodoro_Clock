#include "ClockTower_Hardware.h"

#include "main.h"

void ClockTower_Hardware_getSysTickCount(uint32_t *out_u32SysTickCount) {
  *out_u32SysTickCount = HAL_GetTick();
}
