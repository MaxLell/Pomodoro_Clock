#include "Arduino.h"
#include "Common.h"

static const u8 u8LedPin = 2;

void BlinkyLed_init(void)
{
    pinMode(u8LedPin, OUTPUT);
}

void BlinkyLed_enable(void)
{
    digitalWrite(u8LedPin, HIGH);
}

void BlinkyLed_disable(void)
{
    digitalWrite(u8LedPin, LOW);
}

void BlinkyLed_toggle(void)
{
    static bool sToggle = false;
    sToggle = !sToggle;
    digitalWrite(u8LedPin, (sToggle == true ? HIGH : LOW));
}