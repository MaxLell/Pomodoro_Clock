#include "RgbLed_Hardware.h"
#include "main.h"
#include "tim.h"

void RgbLed_Hardware_init(void)
{
    // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void RgbLed_SetLeds(uint16_t *au16PwmData, uint16_t u16PwmDataSize)
{
    // HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)au16PwmData, u16PwmDataSize);
}