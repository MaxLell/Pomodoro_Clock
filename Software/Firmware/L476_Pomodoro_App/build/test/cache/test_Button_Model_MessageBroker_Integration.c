#include "App/MessageBroker/MessageBroker.h"
#include "src/Button_Model.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



uint8_t u8CallCounter = 0;



status_t ButtonEventCallback(MessageBroker_message_t in_tMessage)

{











    u8CallCounter++;

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((u8CallCounter)), (((void*)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((E_TRIGGER_BUTTON_EVENT)), (UNITY_INT)((in_tMessage.eMsgTopic)), (((void*)0)), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((in_tMessage.u16DataSize)), (((void*)0)), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((in_tMessage.au32Data[0])), (((void*)0)), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);



    return (0);

}



void test_Button_Model_publishData_ShallSendOutAValidMessage(void)

{

    MessageBroker_init();

    MessageBroker_subscribe(E_TRIGGER_BUTTON_EVENT, ButtonEventCallback);

    u8CallCounter = 0;



    BOOL bButtonWasPressed = 1;

    Button_Model_publishData(bButtonWasPressed);





    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((u8CallCounter)), (((void*)0)), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_INT);

}



void test_Button_Model_publishData_ShallNotSendOutAnInvalidMessage(void)

{

    MessageBroker_init();

    MessageBroker_subscribe(E_TRIGGER_BUTTON_EVENT, ButtonEventCallback);

    u8CallCounter = 0;



    BOOL bButtonWasPressed = 0;

    Button_Model_publishData(bButtonWasPressed);





    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((u8CallCounter)), (((void*)0)), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

}
