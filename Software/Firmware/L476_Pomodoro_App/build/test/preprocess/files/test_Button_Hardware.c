#include "src/Button_Hardware.h"
#include "build/test/mocks/mock_EXTI.h"
#include "build/test/mocks/mock_GPIO.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_Button_Hardware_init_shall_InitTheGPIOAndEXTIPeripherals()

{

    GPIO_PushButtonPC13_init_CMockExpect(16);

    EXTI_PushButtonPC13_init_CMockExpect(17);



    Button_Hardware_init();

}



void test_Button_Hardware_wasPressed_shall_ReturnTrue_when_ButtonWasPressed()

{



    EXTI_PushButtonPC13_wasPressed_CMockExpectAndReturn(25, 1);



    BOOL bWasPressed = Button_Hardware_wasPressed();



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((bWasPressed)), (((void*)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_Hardware_wasPressed_shall_ReturnFalse_when_ButtonWasNotPressed()

{



    EXTI_PushButtonPC13_wasPressed_CMockExpectAndReturn(35, 0);



    BOOL bWasPressed = Button_Hardware_wasPressed();



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((bWasPressed)), (((void*)0)), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}
