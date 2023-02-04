#include "unity.h"
#include "Button.h"

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

void test_Button_init_should_EnableTheClockForGPIOC()
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->AHB2ENR = 0;

    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;

    Button_init();

    TEST_ASSERT_EQUAL_HEX(RCC_AHB2ENR_GPIOCEN, RCC->AHB2ENR);
}

void test_Button_init_should_SetModeToInput()
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;

    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;
    GPIOC->MODER = 0;

    Button_init();
    TEST_ASSERT_EQUAL_HEX(!GPIO_MODER_MODE13_1, GPIOC->MODER);
    TEST_ASSERT_EQUAL_HEX(!GPIO_MODER_MODE13_0, GPIOC->MODER);
}

void test_Button_getState_should_ReturnPressed_when_ButtonIsPressed()
{
    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;

    /* Set to low - Button is pressed */
    GPIOC->IDR &= ~BIT_TO_MASK(13);

    Button_State state = Button_getState();

    TEST_ASSERT_EQUAL(BUTTON_PRESSED, state);
}

void test_Button_getState_should_ReturnReleased_when_ButtonIsReleased()
{
    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;

    /* Set to low - Button is pressed */
    GPIOC->IDR |= BIT_TO_MASK(13);

    Button_State state = Button_getState();

    TEST_ASSERT_EQUAL(BUTTON_RELEASED, state);
}