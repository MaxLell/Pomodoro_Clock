#include "Delay.h"

#include "Common.h"
#include "main.h"

void Delay_ms(uint32_t u32DelayMs) { HAL_Delay(u32DelayMs); }

void Delay_sec(uint32_t u32DelaySec) {
  for (uint32_t i = 0; i < u32DelaySec; i++) {
    Delay_ms(1000);
  }
};