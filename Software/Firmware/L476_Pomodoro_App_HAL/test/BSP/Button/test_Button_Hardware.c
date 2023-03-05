#include "unity.h"
#include "mock_GPIO.h"
#include "mock_EXTI.h"
#include "Button_Hardware.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Button_Hardware_init_shall_InitTheGPIOAndEXTIPeripherals()
{
    GPIO_PushButtonPC13_init_Expect();
    EXTI_PushButtonPC13_init_Expect();

    Button_Hardware_init();
}

void test_Button_Hardware_wasPressed_shall_ReturnTrue_when_ButtonWasPressed()
{
    /* For this case the button is to be pressed */
    EXTI_PushButtonPC13_wasPressed_ExpectAndReturn(TRUE);

    BOOL bWasPressed = Button_Hardware_wasPressed();

    TEST_ASSERT_EQUAL(TRUE, bWasPressed);
}

void test_Button_Hardware_wasPressed_shall_ReturnFalse_when_ButtonWasNotPressed()
{
    /* For this case the button is to be pressed */
    EXTI_PushButtonPC13_wasPressed_ExpectAndReturn(FALSE);

    BOOL bWasPressed = Button_Hardware_wasPressed();

    TEST_ASSERT_EQUAL(FALSE, bWasPressed);
}