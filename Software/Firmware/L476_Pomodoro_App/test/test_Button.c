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

extern Button_State button_state;
extern void Button_isrHandler();
extern void Button_initISR();

void test_Button_init_should_EnableTheClockForGPIOC()
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;
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
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

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
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    /* Set to low - Button is pressed */
    GPIOC->IDR &= ~BIT_TO_MASK(13);

    Button_State state = Button_getState();

    TEST_ASSERT_EQUAL(BUTTON_PRESSED, state);
}

void test_Button_getState_should_ReturnReleased_when_ButtonIsReleased()
{
    GPIO_TypeDef gpio_c;
    GPIOC = &gpio_c;
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    /* Set to low - Button is pressed */
    GPIOC->IDR |= BIT_TO_MASK(13);

    Button_State state = Button_getState();

    TEST_ASSERT_EQUAL(BUTTON_RELEASED, state);
}

void test_Button_initISR_should_EnableTheSYSCFGClock(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    RCC->APB2ENR = 0;

    Button_initISR();

    TEST_ASSERT_EQUAL_HEX(RCC_APB2ENR_SYSCFGEN, RCC->APB2ENR);
}

void test_Button_initISR_should_RouteTheButtonSignalToTheEXTI(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    SYSCFG->EXTICR[3] = 0;

    Button_initISR();

    TEST_ASSERT_EQUAL_HEX(0x20, SYSCFG->EXTICR[3]);
}

void test_Button_initISR_should_EnableISRMaskRegister(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    EXTI->IMR1 = 0;

    Button_initISR();

    TEST_ASSERT_EQUAL_HEX(EXTI_IMR1_IM13, EXTI->IMR1);
}

void test_Button_initISR_should_SetTheTriggerToFallingEdge(void)
{

    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    EXTI->FTSR1 = 0;

    Button_initISR();

    TEST_ASSERT_EQUAL_HEX(EXTI_FTSR1_FT13, EXTI->FTSR1);
}

void test_Button_initISR_should_SetISRPriority(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    NVIC->IP[(uint32_t)EXTI15_10_IRQn] = 0;

    Button_initISR();

    TEST_ASSERT_EQUAL_HEX(0, NVIC->IP[(uint32_t)EXTI15_10_IRQn]);
}

void test_Button_initISR_should_EnableTheInterrupt(void)
{
    /**
     * this function does not do much - it does not check the NVIC function
     * rather then that it checks if the code cras
     */
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void test_Button_isrHandler_should_ClearPendingRegister(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    SYSCFG_TypeDef syscfg;
    SYSCFG = &syscfg;
    EXTI_TypeDef exti;
    EXTI = &exti;
    NVIC_Type viccy;
    NVIC = &viccy;
    SCB_Type sibby;
    SCB = &sibby;

    EXTI->PR1 = 0;

    Button_isrHandler();

    TEST_ASSERT_EQUAL_HEX(EXTI_PR1_PIF13, EXTI->PR1);
}

void test_Button_isrHandler_should_UpdateTheButtonState(void)
{
    button_state = BUTTON_RELEASED;

    Button_isrHandler();

    TEST_ASSERT_EQUAL(BUTTON_PRESSED, button_state);
}

void test_Button_wasPressed_should_ReturnTrue_when_ButtonWasPressed(void)
{
    button_state = BUTTON_PRESSED;
    BOOL result = Button_wasPressed();
    TEST_ASSERT_EQUAL(TRUE, result);
}

void test_Button_wasPressed_should_ReturnFalse_when_ButtonWasNotPressed(void)
{
    button_state = BUTTON_RELEASED;
    BOOL result = Button_wasPressed();
    TEST_ASSERT_EQUAL(FALSE, result);
}

void test_Button_wasPressed_should_ResetTheReadingStatus_when_Called(void)
{
    button_state = BUTTON_PRESSED;
    BOOL tmp = Button_wasPressed();

    BOOL result = Button_wasPressed();
    TEST_ASSERT_EQUAL(FALSE, result);
}
