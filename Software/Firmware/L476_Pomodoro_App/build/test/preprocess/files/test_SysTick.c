#include "App/Support/RegisterAccess.h"
#include "App/Support/DbgMacros.h"
#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Drivers/SysTick/SysTick.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












extern uint32_t msTicks;

void test_SysTick_Handler_should_increment_counter()

{

    msTicks = 0;

    SysTick_Handler();

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((msTicks)), (((void*)0)), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_INT);

}
