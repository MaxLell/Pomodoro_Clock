#include "unity.h"
#include "BlinkyLed.h"

#define EXTERN

#include "stm32l476xx.h"

#include "Common.h"
#include "DbgMacros.h"
#include "RegisterAccess.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_BlinkyLed_init_should_EnableTheClockForGPIOA(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->AHB2ENR = 0;

    /**
     * This needs to be specified, otherwise the
     * GPIOA is undefined. This leads to a segfault
     * Therefore it also needs to be mocked at this
     * point
     */
    GPIO_TypeDef gpio_a;
    GPIOA = &gpio_a;

    BlinkyLed_init();

    TEST_ASSERT_EQUAL_HEX(RCC_AHB2ENR_GPIOAEN, RCC->AHB2ENR);
}

void test_BlinkyLed_init_should_SetTheGPIOModeToOutput(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;

    GPIO_TypeDef gpio_a;
    GPIOA = &gpio_a;
    GPIOA->MODER = 0;

    BlinkyLed_init();

    TEST_ASSERT_EQUAL_HEX(GPIO_MODER_MODE5_0, GPIOA->MODER);
}

void test_BlinkyLed_enable_should_SetTheOutputPinToHigh(void)
{
    GPIO_TypeDef gpio_a;
    GPIOA = &gpio_a;
    GPIOA->BSRR = 0;

    BlinkyLed_enable();

    TEST_ASSERT_EQUAL_HEX(GPIO_BSRR_BS_5, GPIOA->BSRR);
}

void test_BlinkyLed_enable_should_SetTheOutputPinToLow(void)
{
    GPIO_TypeDef gpio_a;
    GPIOA = &gpio_a;
    GPIOA->BSRR = 0;

    BlinkyLed_disable();

    TEST_ASSERT_EQUAL_HEX(GPIO_BSRR_BR_5, GPIOA->BSRR);
}

void test_BlinkyLed_toggle_should_ToggleTheOutputPin(void)
{
    GPIO_TypeDef gpio_a;
    GPIOA = &gpio_a;
    // GPIOA->IDR = BIT_TO_MASK(5);

    /* Set the LED Output to low - should be toggled high */
    GPIOA->IDR = 0;
    GPIOA->BSRR = 0;

    BlinkyLed_toggle();

    TEST_ASSERT_EQUAL_HEX(GPIO_BSRR_BS_5, GPIOA->BSRR);

    /* Set the LED Output to high - should be toggled low */
    GPIOA->IDR |= BIT_TO_MASK(5);
    GPIOA->BSRR = 0;

    BlinkyLed_toggle();

    // TEST_ASSERT_EQUAL_HEX(GPIO_BSRR_BR_5, GPIOA->BSRR);
    TEST_ASSERT_EQUAL_HEX(GPIO_BSRR_BR_5, GPIOA->BSRR);
}
