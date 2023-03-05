#ifndef GPIO_H
#define GPIO_H

void GPIO_PushButtonPC13_init();

void GPIO_BlinkyLedPA5_init();
void GPIO_BlinkyLedPA5_enable();
void GPIO_BlinkyLedPA5_disable(void);
void GPIO_BlinkyLedPA5_toggle(void);

#endif // GPIO_H