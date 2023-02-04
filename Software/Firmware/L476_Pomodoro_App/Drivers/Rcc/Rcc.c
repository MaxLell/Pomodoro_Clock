#include "Rcc.h"

#include "Common.h"
#include "stm32l476xx.h"
#include "RegisterAccess.h"

STATIC uint8_t spy_variable_for_test;

STATIC void Rcc_EnableHsiClockAndWaitForReady(void)
{
    /**
     * Set the clock input to the HSION
     * (Source RM0351 Rev 9 225/1906)
     */
    RCC->CR |= RCC_CR_HSION;

    /**
     * Wait for the HSI to be stable and ready to use
     * (Source RM0351 Rev 9 224/1906)
     */
    while ((RCC->CR & RCC_CR_HSIRDY) == 0)
    {
        if (!FOREVER)
        {
            /**
             * This is for testing only
             * FOREVER is set to 0 when the tests
             * are executed. Otherwise the test is
             * stuck infinitly in the loop
             */
            spy_variable_for_test = STATUS_MISSING_DATA;

            break;
        }
    }
}

STATIC void Rcc_SetTheFlashRCCSettings(void)
{

    /**
     * We cannot access Flash as fast as the MCU goes
     * this needs to happen slower (But for the L4 this
     * depends on the previously setup Power Scheme).
     * Nonetheless - clear all the flags.
     * Source (RM0351 Rev 9 125/1906)
     */
    FLASH->ACR &= ~(FLASH_ACR_LATENCY);

    /**
     * Enable the Prefetch Buffer
     * This is a memory between the Flash and the RAM, which also needs to
     * be enabled
     * Source (RM0351 Rev 9 125/1906)
     */
    FLASH->ACR |= FLASH_ACR_PRFTEN;
}

STATIC void Rcc_SetHSIAsMainSysClockAndWaitForReady(void)
{
    /**
     * Set HSI as the Source for the System Clock
     * (Source RM0351 Rev 9 229/1906)
     */
    RCC->CFGR &= ~(RCC_CFGR_SW); /* Clear the bits */
    RCC->CFGR |= RCC_CFGR_SW_0;

    /**
     * Wait until the Clock is ready
     * (Source RM0351 Rev 9 228/1906)
     */
    while (((RCC->CFGR & RCC_CFGR_SWS_0) == 0))
    {
        if (!FOREVER)
        {
            spy_variable_for_test = STATUS_MISSING_DATA;
            break;
        }
    }
}

STATIC void Rcc_SetPeripheralClockDividers(void)
{
    /* AHB Prescaler = 1*/
    RCC->CFGR &= ~(RCC_CFGR_HPRE);

    /* APB1 / PCLK1 Prescaler = 1*/
    RCC->CFGR &= ~(RCC_CFGR_PPRE1);

    /* APB2 / PCLK2 Prescaler = 1 */
    RCC->CFGR &= ~(RCC_CFGR_PPRE2);
}

STATIC void Rcc_EnableMCOAndOutputSystemClock(void)
{
    /**/
    RCC->CFGR &= ~RCC_CFGR_MCOPRE; /* Clear */
    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV16;

    /* Output the System Clock */
    RCC->CFGR &= ~RCC_CFGR_MCOSEL; /* Clear */
    RCC->CFGR |= RCC_CFGR_MCOSEL_0;

    /* Set the GPIO Output Clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
}

void Rcc_init(void)
{
    Rcc_EnableHsiClockAndWaitForReady();

    Rcc_SetTheFlashRCCSettings();

    Rcc_SetHSIAsMainSysClockAndWaitForReady();

    Rcc_SetPeripheralClockDividers();

    // Rcc_EnableMCOAndOutputSystemClock();
}
