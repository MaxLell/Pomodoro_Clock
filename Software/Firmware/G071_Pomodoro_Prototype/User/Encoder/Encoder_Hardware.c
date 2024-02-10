#include "Encoder_Hardware.h"
#include "main.h"
#include "tim.h"

void Encoder_Hardware_init() 
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // Timer for the Rotary Encoder
}

void Encoder_Hardware_getCurrentEncoderValue(int32_t* const out_ps32Value)
{
    ASSERT_MSG(!(out_ps32Value == NULL), "out_ps32Value is NULL");
    *out_ps32Value = (int32_t) __HAL_TIM_GetCounter(&htim2);
}

void Encoder_Hardware_resetEncoderValue()
{
    __HAL_TIM_SetCounter(&htim2, 0);
}