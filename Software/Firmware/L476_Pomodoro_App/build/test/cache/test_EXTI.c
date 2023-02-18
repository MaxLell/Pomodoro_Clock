#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Drivers/EXTI/EXTI.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (0U)))), (UNITY_INT)(UNITY_INT32)((RCC->APB2ENR)), (((void*)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0x20)), (UNITY_INT)(UNITY_INT32)((SYSCFG->EXTICR[3])), (((void*)0)), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->IMR1)), (((void*)0)), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->FTSR1)), (((void*)0)), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0)), (UNITY_INT)(UNITY_INT32)((NVIC->IP[(uint32_t)EXTI15_10_IRQn])), (((void*)0)), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_HEX32);

}



void test_EXTI_PushButtonPC13_init_should_EnableTheInterrupt(void)

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



    __NVIC_EnableIRQ(EXTI15_10_IRQn);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->PR1)), (((void*)0)), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_HEX32);

}

extern BOOL EXTI_PushButtonPC13_bWasPressed;

extern void EXTI_PushButtonPC13_isrHandler();



void test_Button_isrHandler_should_UpdateTheButtonState(void)

{

    EXTI_PushButtonPC13_bWasPressed = 0;

    EXTI_PushButtonPC13_isrHandler();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((EXTI_PushButtonPC13_bWasPressed)), (((void*)0)), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_INT);

}



void test_EXTI_PushButtonPC13_wasPressed_should_ReturnTrue_when_ButtonWasPressed(void)

{

    EXTI_PushButtonPC13_bWasPressed = 0;

    EXTI_PushButtonPC13_isrHandler();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((EXTI_PushButtonPC13_bWasPressed)), (((void*)0)), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_INT);



    BOOL result = EXTI_PushButtonPC13_wasPressed();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(174), UNITY_DISPLAY_STYLE_INT);

}



void test_EXTI_PushButtonPC13_wasPressed_should_ReturnFalse_when_ButtonWasNotPressed(void)

{

    EXTI_PushButtonPC13_bWasPressed = 0;

    EXTI_PushButtonPC13_isrHandler();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((EXTI_PushButtonPC13_bWasPressed)), (((void*)0)), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_INT);



    BOOL result = EXTI_PushButtonPC13_wasPressed();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(184), UNITY_DISPLAY_STYLE_INT);

}



void test_EXTI_PushButtonPC13_wasPressed_should_ResetTheReadingStatus_when_Called(void)

{

    EXTI_PushButtonPC13_bWasPressed = 1;

    BOOL result = EXTI_PushButtonPC13_wasPressed();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((EXTI_PushButtonPC13_bWasPressed)), (((void*)0)), (UNITY_UINT)(193), UNITY_DISPLAY_STYLE_INT);



    EXTI_PushButtonPC13_bWasPressed = 0;

    result = EXTI_PushButtonPC13_wasPressed();

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(197), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((EXTI_PushButtonPC13_bWasPressed)), (((void*)0)), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_INT);

}
