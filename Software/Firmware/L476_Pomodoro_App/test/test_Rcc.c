#include "unity.h"
#include "Rcc.h"

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

extern void Rcc_EnableHsiClockAndWaitForReady(void);
void test_Rcc_Init_should_EnableHSIClock(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->CR = 0;

    Rcc_EnableHsiClockAndWaitForReady();

    TEST_ASSERT_EQUAL_HEX(RCC_CR_HSION, RCC->CR);
}
extern uint8_t spy_variable_for_test;
void test_Rcc_Init_should_WaitUntilHSIClockIsStable(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;

    /* Negative case */
    RCC->CR = 0;
    Rcc_EnableHsiClockAndWaitForReady();
    TEST_ASSERT_EQUAL(STATUS_MISSING_DATA, spy_variable_for_test);

    /* Positive Case */
    RCC->CR = 0;
    spy_variable_for_test = STATUS_OK;
    RCC->CR |= RCC_CR_HSIRDY;
    Rcc_EnableHsiClockAndWaitForReady();
    TEST_ASSERT_EQUAL(STATUS_OK, spy_variable_for_test);
}

extern void Rcc_SetHSIAsMainSysClockAndWaitForReady();
void test_Rcc_Init_should_SetHSIAsMainClockSource(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->CFGR = 0;

    Rcc_SetHSIAsMainSysClockAndWaitForReady();

    TEST_ASSERT_EQUAL(RCC_CFGR_SWS_0, (RCC->CFGR & RCC_CFGR_SWS_0));
    TEST_ASSERT_NOT_EQUAL(RCC_CFGR_SWS_1, (RCC->CFGR & RCC_CFGR_SWS_1));
}

extern void Rcc_SetTheFlashRCCSettings(void);
void test_Rcc_Init_should_SetUpFlash(void)
{
    FLASH_TypeDef flaschi;
    FLASH = &flaschi;
    FLASH->ACR |= FLASH_ACR_LATENCY;

    Rcc_SetTheFlashRCCSettings();

    TEST_ASSERT_EQUAL(FLASH_ACR_PRFTEN, (FLASH->ACR & FLASH_ACR_PRFTEN));
    TEST_ASSERT_NOT_EQUAL(FLASH_ACR_LATENCY, (FLASH->ACR & FLASH_ACR_LATENCY));
}

extern void Rcc_SetPeripheralClockDividers(void);
void test_Rcc_Init_should_SetUpThePeripheralClockDeviders(void)
{
    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->CFGR = 0xFFFFFFFF;

    RCC->CFGR &= ~(RCC_CFGR_HPRE);
    RCC->CFGR &= ~(RCC_CFGR_PPRE1);
    RCC->CFGR &= ~(RCC_CFGR_PPRE2);

    Rcc_SetPeripheralClockDividers();

    TEST_ASSERT_EQUAL_HEX(!RCC_CFGR_HPRE, (RCC->CFGR & RCC_CFGR_HPRE));
    TEST_ASSERT_EQUAL_HEX(!RCC_CFGR_PPRE1, (RCC->CFGR & RCC_CFGR_PPRE1));
    TEST_ASSERT_EQUAL_HEX(!RCC_CFGR_PPRE2, (RCC->CFGR & RCC_CFGR_PPRE2));
}

void test_Rcc_Init_should_EnableMcoOfTheSysclock(void)
{

    RCC_TypeDef Dummy;
    RCC = &Dummy;
    RCC->CFGR = 0xFFFFFFFF;

    /**/
    RCC->CFGR &= ~RCC_CFGR_MCOPRE; /* Clear */
    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV16;

    /* Output the System Clock */
    RCC->CFGR &= ~RCC_CFGR_MCOSEL; /* Clear */
    RCC->CFGR |= RCC_CFGR_MCOSEL_0;

    TEST_ASSERT_EQUAL_HEX(RCC_CFGR_MCOPRE_DIV16, (RCC->CFGR & RCC_CFGR_MCOPRE_DIV16));
    TEST_ASSERT_EQUAL_HEX(RCC_CFGR_MCOSEL_0, (RCC->CFGR & RCC_CFGR_MCOSEL_0));
}