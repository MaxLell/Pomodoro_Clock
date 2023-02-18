#include "unity.h"
#include "GPIO.h"

#define EXTERN

#include "stm32l476xx.h"
#include "Common.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_GPIO_PushButtonPC13_init_should_EnableTheClockForGPIOC()
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;

    RCC->AHB2ENR = 0;

    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;

    GPIO_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(RCC_AHB2ENR_GPIOCEN, RCC->AHB2ENR);
}

void test_GPIO_PushButtonPC13_init_should_SetModeToInput()
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;

    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;
    GPIOC->MODER = 0;

    GPIO_PushButtonPC13_init();
    TEST_ASSERT_EQUAL_HEX(!GPIO_MODER_MODE13_1, GPIOC->MODER);
    TEST_ASSERT_EQUAL_HEX(!GPIO_MODER_MODE13_0, GPIOC->MODER);
}
