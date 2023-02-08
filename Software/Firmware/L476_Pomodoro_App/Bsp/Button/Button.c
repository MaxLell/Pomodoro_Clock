#include "Button.h"

#include "Common.h"
#include "stm32l476xx.h"
#include "RegisterAccess.h"

/**
 * The button is connected to PC13
 * on the Nucleo Board
 *
 * Important is: The logic is inverse:
 * Button pressed -> Signal Low
 * Button released -> Signal High
 *
 * The pin is connected to a Pull up resistor.
 */

/**
 * Ressources:
 * https://controllerstech.com/stm32-gpio-input-configuration/
 */

STATIC Button_State button_state = BUTTON_RELEASED;

STATIC void Button_initISR()
{
    /* Enable the SYSCFG Clock */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /**
     * Source: RM0351 Rev 9 - 321/1906
     * Set the SYSCFG register
     *
     * Information Source: https://youtu.be/IKUARhb2iFU @ 5:20
     * It really needs to be done with
     * the EXTICR_4 but it is wrapped
     * into an array, therefore 3 needs
     * to be used as an index
     *
     * This maps PC13 to the EXTI13
     */

    SYSCFG->EXTICR[3] &= ~(0b0000 << 4); // Clear before writing
    SYSCFG->EXTICR[3] |= (0b0010 << 4);  // Set the relevant bits

    /**
     * EXTI IMR
     * When the ISR is masked - then it means that it is disabled
     * The Masked register also needs to be set
     *
     * PA13, PB13, PC13, ..., PF13 are routed to EXTI13
     */
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    /**
     * Set the Falling Edge
     * It needs to be a falling edge, as the Push Button
     * is logic negative connected to the Microcontroller.
     */
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;

    /**
     * Set the Interrupt Priority
     */
    NVIC_SetPriority(EXTI15_10_IRQn, 0);

    /**
     * Enable the Interrupt
     */
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void Button_init()
{
    /* Enable GPIOC Clock*/
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Set the Mode Register to 0 for Pin 13 - Input Mode */
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_0);
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_1);

    /* Set up the ISR Channel for the button */
    Button_initISR();
}

Button_State Button_getState()
{
    Button_State tmp;
    if ((GPIOC->IDR & (1 << 13)))
    {
        tmp = BUTTON_RELEASED;
    }
    else
    {
        tmp = BUTTON_PRESSED;
    }
    return tmp;
}

BOOL Button_wasPressed()
{
    /**
     * This clears the Button Flag
     * when this function is called
     */
    BOOL tmp = button_state;
    button_state = BUTTON_RELEASED;
    return (tmp == BUTTON_PRESSED) ? TRUE : FALSE;
}

STATIC void Button_isrHandler(void)
{
    /**
     * Pending Bit needs to be cleared otherwise
     * the ISR will fire continuously.
     */

    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    EXTI->PR1 |= EXTI_PR1_PIF13;

    /* Space for application code */
    button_state = BUTTON_PRESSED;
}

void EXTI15_10_IRQHandler(void)
{
    Button_isrHandler();
}