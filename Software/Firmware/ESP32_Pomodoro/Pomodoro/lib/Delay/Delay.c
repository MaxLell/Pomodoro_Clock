#include "Delay.h"
#include "Common.h"
#include "Arduino.h"

void Delay_ms(u32 u32DelayMs)
{
  vTaskDelay(u32DelayMs / portTICK_PERIOD_MS);
}

void Delay_sec(u32 u32DelaySec)
{
  for (u32 i = 0; i < u32DelaySec; i++)
  {
    Delay_ms(1000);
  }
};