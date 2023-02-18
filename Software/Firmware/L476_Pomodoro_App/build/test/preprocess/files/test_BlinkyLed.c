#include "Drivers/GPIO/GPIO.h"
#include "App/Support/RegisterAccess.h"
#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Bsp/BlinkyLed/BlinkyLed.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












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















    GPIO_TypeDef gpio_a;

    GPIOA = &gpio_a;



    BlinkyLed_init();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (0U)))), (UNITY_INT)(UNITY_INT32)((RCC->AHB2ENR)), (((void*)0)), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX32);

}



void test_BlinkyLed_init_should_SetTheGPIOModeToOutput(void)

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;



    GPIO_TypeDef gpio_a;

    GPIOA = &gpio_a;

    GPIOA->MODER = 0;



    BlinkyLed_init();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (10U)))), (UNITY_INT)(UNITY_INT32)((GPIOA->MODER)), (((void*)0)), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_HEX32);

}



void test_BlinkyLed_enable_should_SetTheOutputPinToHigh(void)

{

    GPIO_TypeDef gpio_a;

    GPIOA = &gpio_a;

    GPIOA->BSRR = 0;



    BlinkyLed_enable();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (5U)))), (UNITY_INT)(UNITY_INT32)((GPIOA->BSRR)), (((void*)0)), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_HEX32);

}



void test_BlinkyLed_enable_should_SetTheOutputPinToLow(void)

{

    GPIO_TypeDef gpio_a;

    GPIOA = &gpio_a;

    GPIOA->BSRR = 0;



    BlinkyLed_disable();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (21U)))), (UNITY_INT)(UNITY_INT32)((GPIOA->BSRR)), (((void*)0)), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_HEX32);

}



void test_BlinkyLed_toggle_should_ToggleTheOutputPin(void)

{

    GPIO_TypeDef gpio_a;

    GPIOA = &gpio_a;





    GPIOA->IDR = 0;

    GPIOA->BSRR = 0;



    BlinkyLed_toggle();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (5U)))), (UNITY_INT)(UNITY_INT32)((GPIOA->BSRR)), (((void*)0)), (UNITY_UINT)(88), UNITY_DISPLAY_STYLE_HEX32);





    GPIOA->IDR |= (1u << (5));

    GPIOA->BSRR = 0;



    BlinkyLed_toggle();





    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (21U)))), (UNITY_INT)(UNITY_INT32)((GPIOA->BSRR)), (((void*)0)), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_HEX32);

}
