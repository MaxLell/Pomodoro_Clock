#include "unity.h"

#include "Button_Model.h"
#include "mock_MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Button_Model_publishData_Shall_PublishAMessageWithTheMessageBroker(void)
{
    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    BOOL bButtonWasPressed = TRUE;
    Button_Model_publishData(bButtonWasPressed);
}