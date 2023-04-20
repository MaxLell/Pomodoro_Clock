#include "build/test/mocks/mock_MessageBroker.h"
#include "build/test/mocks/mock_RealTimeClock_Hardware.h"
#include "User/RealTimeClock/RealTimeClock.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}











extern status_t RealTimeClock_publishTimeAndDate(RealTimeClock_TimeAndDate_t in_sTimeAndDate);

void test_RealTimeClock_publishTimeAndDate_should_PublishTheProvidedTimeAndDateViaTheMessageBroker(void)

{



    RealTimeClock_TimeAndDate_t tTimeAndDate = {0};

    tTimeAndDate.u8Hour = 12;

    tTimeAndDate.u8Minute = 34;

    tTimeAndDate.u8Second = 56;

    tTimeAndDate.u8Day = 1;

    tTimeAndDate.u8Month = 2;

    tTimeAndDate.u8Year = 3;



    MessageBroker_message_t tMessage = {0};

    tMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    tMessage.u16DataSize = 6U;

    tMessage.au8DataBytes = (uint8_t *)&tTimeAndDate;



    MessageBroker_publish_CMockIgnoreAndReturn(37, (0));





    status_t tStatus = RealTimeClock_publishTimeAndDate(tTimeAndDate);





    UnityAssertEqualNumber((UNITY_INT)(((0))), (UNITY_INT)((tStatus)), (((void*)0)), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

}













void test_RealTimeClock_init_should_SubscribeToTheE_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSEDTopic(void)

{



    MessageBroker_subscribe_CMockIgnoreAndReturn(54, (0));





    RealTimeClock_init();





}
