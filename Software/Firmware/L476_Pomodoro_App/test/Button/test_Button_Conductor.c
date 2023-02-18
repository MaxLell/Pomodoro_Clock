#include "unity.h"

#include "mock_Button_Model.h"
#include "mock_Button_Hardware.h"
#include "Button_Conductor.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Button_Conductor_init_shall_InitializeModelAndHardware(void)
{
    Button_Hardware_init_Expect();

    Button_Conductor_init();
}

void test_Button_Conductor_exec_shall_PublishData_when_aNewButtonEventHappend()
{
    /* First example: Button was pressed */
    BOOL bButtonWasPressed = TRUE;

    Button_Hardware_wasPressed_ExpectAndReturn(bButtonWasPressed);
    Button_Model_publishData_Expect(bButtonWasPressed);

    Button_Conductor_exec();
}

void test_Button_Conductor_exec_shall_NotPublishData_when_aNoNewButtonEventHappend()
{
    /* First example: Button was pressed */
    BOOL bButtonWasPressed = FALSE;

    Button_Hardware_wasPressed_ExpectAndReturn(bButtonWasPressed);

    Button_Conductor_exec();
}
