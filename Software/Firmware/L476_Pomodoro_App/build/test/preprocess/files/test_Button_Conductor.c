#include "src/Button_Conductor.h"
#include "build/test/mocks/mock_Button_Hardware.h"
#include "build/test/mocks/mock_Button_Model.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_Button_Conductor_init_shall_InitializeModelAndHardware(void)

{

    Button_Hardware_init_CMockExpect(17);



    Button_Conductor_init();

}



void test_Button_Conductor_exec_shall_PublishData_when_aNewButtonEventHappend()

{



    BOOL bButtonWasPressed = 1;



    Button_Hardware_wasPressed_CMockExpectAndReturn(27, bButtonWasPressed);

    Button_Model_publishData_CMockExpect(28, bButtonWasPressed);



    Button_Conductor_exec();

}



void test_Button_Conductor_exec_shall_NotPublishData_when_aNoNewButtonEventHappend()

{



    BOOL bButtonWasPressed = 0;



    Button_Hardware_wasPressed_CMockExpectAndReturn(38, bButtonWasPressed);



    Button_Conductor_exec();

}
