#ifndef ENCODER_HARDWARE_H
#define ENCODER_HARDWARE_H

#include "Common.h"

void Encoder_Hardware_init();

void Encoder_Hardware_getCurrentEncoderValue(int32_t* const out_ps32Value);

void Encoder_Hardware_resetEncoderValue();

#endif // ENCODER_HARDWARE_H
