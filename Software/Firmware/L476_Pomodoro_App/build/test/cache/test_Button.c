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



void test_Button_init_should_EnableTheClockForGPIOC()

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;

    RCC->AHB2ENR = 0;



    GPIO_TypeDef gpio_c;

    GPIOC = &gpio_c;



    Button_init();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (2U)))), (UNITY_INT)(UNITY_INT32)((RCC->AHB2ENR)), (((void*)0)), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_HEX32);

}



void test_Button_init_should_SetModeToInput()

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;



    GPIO_TypeDef gpio_c;

    GPIOC = &gpio_c;

    GPIOC->MODER = 0;



    Button_init();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x2UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x1UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_HEX32);

}



void test_Button_getState_should_ReturnPressed_when_ButtonIsPressed()

{

    GPIO_TypeDef gpio_c;

    GPIOC = &gpio_c;





    GPIOC->IDR &= ~(1u << (13));



    Button_State state = Button_getState();



    UnityAssertEqualNumber((UNITY_INT)((BUTTON_PRESSED)), (UNITY_INT)((state)), (((void*)0)), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_getState_should_ReturnReleased_when_ButtonIsReleased()

{

    GPIO_TypeDef gpio_c;

    GPIOC = &gpio_c;





    GPIOC->IDR |= (1u << (13));



    Button_State state = Button_getState();



    UnityAssertEqualNumber((UNITY_INT)((BUTTON_RELEASED)), (UNITY_INT)((state)), (((void*)0)), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_INT);

}
