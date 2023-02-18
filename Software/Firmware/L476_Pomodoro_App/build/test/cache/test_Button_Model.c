#include "build/test/mocks/mock_MessageBroker.h"
#include "Bsp/Button/Button_Model.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_Button_Model_publishData_Shall_PublishAMessageWithTheMessageBroker(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(16, (0));



    BOOL bButtonWasPressed = 1;

    Button_Model_publishData(bButtonWasPressed);

}



void test_Button_Model_publishData_Shall_NotPublishAMessage_when_ButtonWasNotPressed(void)

{

    MessageBroker_publish_CMockIgnoreAndReturn(24, (0));



    BOOL bButtonWasPressed = 0;

    Button_Model_publishData(bButtonWasPressed);

}
