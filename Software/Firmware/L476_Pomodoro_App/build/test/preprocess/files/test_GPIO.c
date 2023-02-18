#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Drivers/GPIO/GPIO.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








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



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (2U)))), (UNITY_INT)(UNITY_INT32)((RCC->AHB2ENR)), (((void*)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_HEX32);

}



void test_GPIO_PushButtonPC13_init_should_SetModeToInput()

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;



    GPIO_TypeDef gpio_c;

    GPIOC = &gpio_c;

    GPIOC->MODER = 0;



    GPIO_PushButtonPC13_init();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x2UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x1UL << (26U)))), (UNITY_INT)(UNITY_INT32)((GPIOC->MODER)), (((void*)0)), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX32);

}
