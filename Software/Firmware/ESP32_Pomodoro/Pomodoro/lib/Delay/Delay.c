#include "Delay.h"
#include "Common.h"
#include "Arduino.h"

void Delay_ms(uint32_t u32DelayMs)
{
  vTaskDelay(u32DelayMs / portTICK_PERIOD_MS);
}

void Delay_sec(uint32_t u32DelaySec)
{
  for (uint32_t i = 0; i < u32DelaySec; i++)
  {
    Delay_ms(1000);
  }
};