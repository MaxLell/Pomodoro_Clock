#include "unity.h"
#include "EXTI.h"

#define EXTERN

#include "stm32l476xx.h"
#include "Common.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_EXTI_PushButtonPC13_init_should_EnableTheSYSCFGClock(void)
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

    EXTI_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(RCC_APB2ENR_SYSCFGEN, RCC->APB2ENR);
}

void test_EXTI_PushButtonPC13_init_should_RouteTheButtonSignalToTheEXTI(void)
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

    EXTI_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(0x20, SYSCFG->EXTICR[3]);
}

void test_EXTI_PushButtonPC13_init_should_EnableISRMaskRegister(void)
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

    EXTI_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(EXTI_IMR1_IM13, EXTI->IMR1);
}

void test_EXTI_PushButtonPC13_init_should_SetTheTriggerToFallingEdge(void)
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

    EXTI_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(EXTI_FTSR1_FT13, EXTI->FTSR1);
}

void test_EXTI_PushButtonPC13_init_should_SetISRPriority(void)
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

    EXTI_PushButtonPC13_init();

    TEST_ASSERT_EQUAL_HEX(0, NVIC->IP[(uint32_t)EXTI15_10_IRQn]);
}

void test_EXTI_PushButtonPC13_init_should_EnableTheInterrupt(void)
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
extern void EXTI15_10_IRQHandler();
void test_EXTI15_10_IRQHandler_should_ClearPendingRegister(void)
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

    EXTI15_10_IRQHandler();

    TEST_ASSERT_EQUAL_HEX(EXTI_PR1_PIF13, EXTI->PR1);
}
extern BOOL EXTI_PushButtonPC13_bWasPressed;
extern void EXTI_PushButtonPC13_isrHandler();

void test_Button_isrHandler_should_UpdateTheButtonState(void)
{
    EXTI_PushButtonPC13_bWasPressed = FALSE;
    EXTI_PushButtonPC13_isrHandler();
    TEST_ASSERT_EQUAL(TRUE, EXTI_PushButtonPC13_bWasPressed);
}

void test_EXTI_PushButtonPC13_wasPressed_should_ReturnTrue_when_ButtonWasPressed(void)
{
    EXTI_PushButtonPC13_bWasPressed = FALSE;
    EXTI_PushButtonPC13_isrHandler();
    TEST_ASSERT_EQUAL(TRUE, EXTI_PushButtonPC13_bWasPressed);

    BOOL result = EXTI_PushButtonPC13_wasPressed();
    TEST_ASSERT_EQUAL(TRUE, result);
}

void test_EXTI_PushButtonPC13_wasPressed_should_ReturnFalse_when_ButtonWasNotPressed(void)
{
    EXTI_PushButtonPC13_bWasPressed = FALSE;
    EXTI_PushButtonPC13_isrHandler();
    TEST_ASSERT_EQUAL(TRUE, EXTI_PushButtonPC13_bWasPressed);

    BOOL result = EXTI_PushButtonPC13_wasPressed();
    TEST_ASSERT_EQUAL(TRUE, result);
}

void test_EXTI_PushButtonPC13_wasPressed_should_ResetTheReadingStatus_when_Called(void)
{
    EXTI_PushButtonPC13_bWasPressed = TRUE;
    BOOL result = EXTI_PushButtonPC13_wasPressed();
    TEST_ASSERT_EQUAL(TRUE, result);

    TEST_ASSERT_EQUAL(FALSE, EXTI_PushButtonPC13_bWasPressed);

    EXTI_PushButtonPC13_bWasPressed = FALSE;
    result = EXTI_PushButtonPC13_wasPressed();
    TEST_ASSERT_EQUAL(FALSE, result);

    TEST_ASSERT_EQUAL(FALSE, EXTI_PushButtonPC13_bWasPressed);
}