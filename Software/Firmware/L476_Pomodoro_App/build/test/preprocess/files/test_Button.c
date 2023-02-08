#include "App/Support/RegisterAccess.h"
#include "App/Support/DbgMacros.h"
#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Bsp/Button/Button.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (2U)))), (UNITY_INT)(UNITY_INT32)((RCC->AHB2ENR)), (((void*)0)), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_HEX32);

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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x2UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x1UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_HEX32);

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





    GPIOC->IDR &= ~(1u << (13));



    Button_State state = Button_getState();



    UnityAssertEqualNumber((UNITY_INT)((BUTTON_PRESSED)), (UNITY_INT)((state)), (((void*)0)), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_INT);

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





    GPIOC->IDR |= (1u << (13));



    Button_State state = Button_getState();



    UnityAssertEqualNumber((UNITY_INT)((BUTTON_RELEASED)), (UNITY_INT)((state)), (((void*)0)), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (0U)))), (UNITY_INT)(UNITY_INT32)((RCC->APB2ENR)), (((void*)0)), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0x20)), (UNITY_INT)(UNITY_INT32)((SYSCFG->EXTICR[3])), (((void*)0)), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->IMR1)), (((void*)0)), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->FTSR1)), (((void*)0)), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_HEX32);

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0)), (UNITY_INT)(UNITY_INT32)((NVIC->IP[(uint32_t)EXTI15_10_IRQn])), (((void*)0)), (UNITY_UINT)(211), UNITY_DISPLAY_STYLE_HEX32);

}



void test_Button_initISR_should_EnableTheInterrupt(void)

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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (13U)))), (UNITY_INT)(UNITY_INT32)((EXTI->PR1)), (((void*)0)), (UNITY_UINT)(251), UNITY_DISPLAY_STYLE_HEX32);

}



void test_Button_isrHandler_should_UpdateTheButtonState(void)

{

    button_state = BUTTON_RELEASED;



    Button_isrHandler();



    UnityAssertEqualNumber((UNITY_INT)((BUTTON_PRESSED)), (UNITY_INT)((button_state)), (((void*)0)), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_wasPressed_should_ReturnTrue_when_ButtonWasPressed(void)

{

    button_state = BUTTON_PRESSED;

    BOOL result = Button_wasPressedSinceLastRead();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(267), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_wasPressed_should_ReturnFalse_when_ButtonWasNotPressed(void)

{

    button_state = BUTTON_RELEASED;

    BOOL result = Button_wasPressedSinceLastRead();

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(274), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_wasPressed_should_ResetTheReadingStatus_when_Called(void)

{

    button_state = BUTTON_PRESSED;

    BOOL tmp = Button_wasPressedSinceLastRead();



    BOOL result = Button_wasPressedSinceLastRead();

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (((void*)0)), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_INT);

}
