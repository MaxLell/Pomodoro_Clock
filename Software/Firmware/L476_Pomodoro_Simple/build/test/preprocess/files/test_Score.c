#include "User/PomodoroFsm/PomodoroFsm_Interface.h"
#include "build/test/mocks/mock_MessageBroker.h"
#include "User/Common/Common.h"
#include "User/Score/Score.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










extern void Score_updateDailyScore(void);

extern void Score_resetDailyScore(void);

extern status_t Score_callback(MessageBroker_message_t in_sMessage);









extern uint8_t u8DailyScore;

extern BOOL bPomodoroSequenceCompleted;

extern BOOL bResetTimeAlarm;



void setUp(void)

{

}



void tearDown(void)

{

}





void test_Score_init_ShallSubscribeToTopics(void)

{

    MessageBroker_subscribe_CMockExpectAndReturn(35, E_TOPIC_PFSM_STATE_CHANGED, Score_callback, (0));









    MessageBroker_subscribe_CMockExpectAndReturn(40, E_TOPIC_TIME_AND_DATE, Score_callback, (0));









    Score_init();

}



void test_Score_init_ShallResetLocalStaticValues(void)

{

    MessageBroker_subscribe_CMockIgnoreAndReturn(47, (0));



    bPomodoroSequenceCompleted = 1;

    bResetTimeAlarm = 1;

    u8DailyScore = 5U;



    Score_init();



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((u8DailyScore)), (((void*)0)), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((bPomodoroSequenceCompleted)), (((void*)0)), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_UINT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((bResetTimeAlarm)), (((void*)0)), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT8);

}





void test_Score_callback_ShallParsePfsmStateUpdate(void)

{

    bPomodoroSequenceCompleted = 0;



    MessageBroker_message_t sMessage = {0};



    sMessage.eMsgTopic = E_TOPIC_PFSM_STATE_CHANGED;

    uint8_t au8DataBytes[2] = {0};

    sMessage.au8DataBytes = au8DataBytes;

    sMessage.au8DataBytes[0U] = E_PFSM_STATE_BREAKTIME;

    sMessage.au8DataBytes[1U] = E_PFSM_STATE_WORKTIME;



    Score_callback(sMessage);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((bPomodoroSequenceCompleted)), (((void*)0)), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

}



void test_Score_callback_ShallParseTimeUpdate(void)

{

    bResetTimeAlarm = 0;



    MessageBroker_message_t sMessage = {0};



    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;

    uint8_t au8DataBytes[3] = {0};

    sMessage.au8DataBytes = au8DataBytes;

    sMessage.au8DataBytes[2] = 3;

    sMessage.au8DataBytes[1] = 0;



    Score_callback(sMessage);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((bResetTimeAlarm)), (((void*)0)), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_INT);

}



void test_Score_updateScore_ShallIncrementScore(void)

{

    u8DailyScore = 0U;

    Score_updateDailyScore();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((u8DailyScore)), (((void*)0)), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_UINT8);

}





void test_Score_execute_ShallIncrementScoreAndResetTheFlag(void)

{

    u8DailyScore = 0U;

    bPomodoroSequenceCompleted = 1;

    bResetTimeAlarm = 0;



    MessageBroker_publish_CMockIgnoreAndReturn(109, (0));



    Score_execute();



    UnityAssertEqualNumber((UNITY_INT)((1U)), (UNITY_INT)((u8DailyScore)), (((void*)0)), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((bPomodoroSequenceCompleted)), (((void*)0)), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);

}





void test_Score_execute_ShallResetScoreAndResetTheFlag(void)

{

    u8DailyScore = 5U;

    bPomodoroSequenceCompleted = 0;

    bResetTimeAlarm = 1;



    MessageBroker_publish_CMockIgnoreAndReturn(124, (0));



    Score_execute();



    UnityAssertEqualNumber((UNITY_INT)((0U)), (UNITY_INT)((u8DailyScore)), (((void*)0)), (UNITY_UINT)(128), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((bResetTimeAlarm)), (((void*)0)), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_INT);

}
