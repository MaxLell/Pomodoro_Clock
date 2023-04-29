#ifndef RGBLED_H
#define RGBLED_H
#include "Common.h"

typedef struct
{
    uint8_t u8Index;
    uint8_t u8Red;
    uint8_t u8Green;
    uint8_t u8Blue;
} RgbLed_t;

void RgbLed_init(void);

void RgbLed_execute(void);

#endif // RGBLED_H
