#include "User/MessageBroker/MessageBroker.h"
#include "build/test/mocks/mock_RealTimeClock_Hardware.h"
#include "User/RealTimeClock/RealTimeClock.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



RealTimeClock_TimeAndDate_t tTimeAndDate = {0};





status_t dummy_messageCallback(MessageBroker_message_t msg)

{

    if (msg.eMsgTopic == E_TOPIC_TIME_AND_DATE)

    {



        __builtin___memcpy_chk (&tTimeAndDate, msg.au8DataBytes, msg.u16DataSize, __builtin_object_size (&tTimeAndDate, 0));

    }

    return (0);

}

void test_RealTimeClock_execute_with_MessageBroker_should_PublishTheTimeAndDateViaTheMessageBroker(void)

{



    RealTimeClock_TimeAndDate_t tExpectedTimeAndDate = {0};

    tExpectedTimeAndDate.u8Hour = 12;

    tExpectedTimeAndDate.u8Minute = 34;

    tExpectedTimeAndDate.u8Second = 56;

    tExpectedTimeAndDate.u8Day = 11;

    tExpectedTimeAndDate.u8Month = 3;

    tExpectedTimeAndDate.u8Year = 23;





    MessageBroker_init();





    RealTimeClock_init();







    MessageBroker_message_t tMessage = {0};

    tMessage.eMsgTopic = E_TOPIC_ONE_SECOND_PASSED;

    MessageBroker_publish(tMessage);





    MessageBroker_subscribe(E_TOPIC_TIME_AND_DATE, dummy_messageCallback);





    RealTimeClockHW_getTimeAndDate_CMockExpectAndReturn(67, ((void*)0), (0));

    RealTimeClockHW_getTimeAndDate_CMockIgnoreArg_in_pTimeAndDate(68);

    RealTimeClockHW_getTimeAndDate_CMockReturnMemThruPtr_in_pTimeAndDate(69, &tExpectedTimeAndDate, sizeof(RealTimeClock_TimeAndDate_t));





    RealTimeClock_execute();







    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Hour)), (UNITY_INT)((tTimeAndDate.u8Hour)), (((void*)0)), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Minute)), (UNITY_INT)((tTimeAndDate.u8Minute)), (((void*)0)), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Second)), (UNITY_INT)((tTimeAndDate.u8Second)), (((void*)0)), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Day)), (UNITY_INT)((tTimeAndDate.u8Day)), (((void*)0)), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Month)), (UNITY_INT)((tTimeAndDate.u8Month)), (((void*)0)), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((tExpectedTimeAndDate.u8Year)), (UNITY_INT)((tTimeAndDate.u8Year)), (((void*)0)), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_INT);

}
