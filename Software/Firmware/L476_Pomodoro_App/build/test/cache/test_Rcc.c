#include "App/Support/RegisterAccess.h"
#include "App/Support/DbgMacros.h"
#include "App/Support/Common.h"
#include "Drivers/L476_Mappings/stm32l476xx.h"
#include "Drivers/Rcc/Rcc.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












void setUp(void)

{

}



void tearDown(void)

{

}



extern void Rcc_EnableHsiClockAndWaitForReady(void);

void test_Rcc_Init_should_EnableHSIClock(void)

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;

    RCC->CR = 0;



    Rcc_EnableHsiClockAndWaitForReady();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (8U)))), (UNITY_INT)(UNITY_INT32)((RCC->CR)), (((void*)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_HEX32);

}

extern uint8_t spy_variable_for_test;

void test_Rcc_Init_should_WaitUntilHSIClockIsStable(void)

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;





    RCC->CR = 0;

    Rcc_EnableHsiClockAndWaitForReady();

    UnityAssertEqualNumber((UNITY_INT)(((14))), (UNITY_INT)((spy_variable_for_test)), (((void*)0)), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);





    RCC->CR = 0;

    spy_variable_for_test = (0);

    RCC->CR |= (0x1UL << (10U));

    Rcc_EnableHsiClockAndWaitForReady();

    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((spy_variable_for_test)), (((void*)0)), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_INT);

}



extern void Rcc_SetHSIAsMainSysClockAndWaitForReady();

void test_Rcc_Init_should_SetHSIAsMainClockSource(void)

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;

    RCC->CFGR = 0;



    Rcc_SetHSIAsMainSysClockAndWaitForReady();



    UnityAssertEqualNumber((UNITY_INT)(((0x1UL << (2U)))), (UNITY_INT)(((RCC->CFGR & (0x1UL << (2U))))), (((void*)0)), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_INT);

    do {if ((((0x2UL << (2U))) != ((RCC->CFGR & (0x2UL << (2U)))))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(60)));}} while(0);

}



extern void Rcc_SetTheFlashRCCSettings(void);

void test_Rcc_Init_should_SetUpFlash(void)

{

    FLASH_TypeDef flaschi;

    FLASH = &flaschi;

    FLASH->ACR |= (0x7UL << (0U));



    Rcc_SetTheFlashRCCSettings();



    UnityAssertEqualNumber((UNITY_INT)(((0x1UL << (8U)))), (UNITY_INT)(((FLASH->ACR & (0x1UL << (8U))))), (((void*)0)), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

    do {if ((((0x7UL << (0U))) != ((FLASH->ACR & (0x7UL << (0U)))))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(73)));}} while(0);

}



extern void Rcc_SetPeripheralClockDividers(void);

void test_Rcc_Init_should_SetUpThePeripheralClockDeviders(void)

{

    RCC_TypeDef Dummy;

    RCC = &Dummy;

    RCC->CFGR = 0xFFFFFFFF;



    RCC->CFGR &= ~((0xFUL << (4U)));

    RCC->CFGR &= ~((0x7UL << (8U)));

    RCC->CFGR &= ~((0x7UL << (11U)));



    Rcc_SetPeripheralClockDividers();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0xFUL << (4U)))), (UNITY_INT)(UNITY_INT32)(((RCC->CFGR & (0xFUL << (4U))))), (((void*)0)), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x7UL << (8U)))), (UNITY_INT)(UNITY_INT32)(((RCC->CFGR & (0x7UL << (8U))))), (((void*)0)), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((!(0x7UL << (11U)))), (UNITY_INT)(UNITY_INT32)(((RCC->CFGR & (0x7UL << (11U))))), (((void*)0)), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_HEX32);

}



void test_Rcc_Init_should_EnableMcoOfTheSysclock(void)

{



    RCC_TypeDef Dummy;

    RCC = &Dummy;

    RCC->CFGR = 0xFFFFFFFF;





    RCC->CFGR &= ~(0x7UL << (28U));

    RCC->CFGR |= (0x40000000UL);





    RCC->CFGR &= ~(0x7UL << (24U));

    RCC->CFGR |= (0x1UL << (24U));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x40000000UL))), (UNITY_INT)(UNITY_INT32)(((RCC->CFGR & (0x40000000UL)))), (((void*)0)), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_HEX32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)(((0x1UL << (24U)))), (UNITY_INT)(UNITY_INT32)(((RCC->CFGR & (0x1UL << (24U))))), (((void*)0)), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_HEX32);

}
