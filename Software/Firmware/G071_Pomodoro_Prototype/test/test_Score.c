#include "unity.h"
#include "Score.h"
#include "Common.h"
#include "mock_MessageBroker.h"
#include "PomodoroFsm_Interface.h"

/**
 * External Functions
 */
extern void Score_updateDailyScore(void);
extern void Score_resetDailyScore(void);
extern status_t Score_callback(MessageBroker_message_t in_sMessage);

/**
 * External Variables
 */
extern uint8_t u8DailyScore;
extern BOOL bPomodoroSequenceCompleted;
extern BOOL bResetTimeAlarm;

void setUp(void)
{
}

void tearDown(void)
{
}

// Score init shall subscribe to the current time and date
void test_Score_init_ShallSubscribeToTopics(void)
{
    MessageBroker_subscribe_ExpectAndReturn(
        E_TOPIC_PFSM_STATE_CHANGED,
        Score_callback,
        STATUS_OK);

    MessageBroker_subscribe_ExpectAndReturn(
        E_TOPIC_TIME_AND_DATE,
        Score_callback,
        STATUS_OK);

    Score_init();
}
// Score init Shall reset the local static values
void test_Score_init_ShallResetLocalStaticValues(void)
{
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    bPomodoroSequenceCompleted = TRUE;
    bResetTimeAlarm = TRUE;
    u8DailyScore = 5U;

    Score_init();

    TEST_ASSERT_EQUAL_UINT8(0U, u8DailyScore);
    TEST_ASSERT_EQUAL_UINT8(FALSE, bPomodoroSequenceCompleted);
    TEST_ASSERT_EQUAL_UINT8(FALSE, bResetTimeAlarm);
}

// Score Callback shall parse the PFSM State update. If the PFSM State Transition is from Worktime to Breaktime, then it shall set the flag
void test_Score_callback_ShallParsePfsmStateUpdate(void)
{
    bPomodoroSequenceCompleted = FALSE;

    MessageBroker_message_t sMessage = {0};

    sMessage.eMsgTopic = E_TOPIC_PFSM_STATE_CHANGED;
    uint8_t au8DataBytes[2] = {0};
    sMessage.au8DataBytes = au8DataBytes;
    sMessage.au8DataBytes[PFSM_NEW_STATE] = E_PFSM_STATE_BREAKTIME;
    sMessage.au8DataBytes[PFSM_OLD_STATE] = E_PFSM_STATE_WORKTIME;

    Score_callback(sMessage);

    TEST_ASSERT_EQUAL(TRUE, bPomodoroSequenceCompleted);
}
// Score Callback shall check the current time against the set alarm time, if the alarm time is met, it shall set the flag
void test_Score_callback_ShallParseTimeUpdate(void)
{
    bResetTimeAlarm = FALSE;

    MessageBroker_message_t sMessage = {0};

    sMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;
    uint8_t au8DataBytes[3] = {0};
    sMessage.au8DataBytes = au8DataBytes;
    sMessage.au8DataBytes[TIME_DATE_HOUR] = 3;
    sMessage.au8DataBytes[TIME_DATE_MINUTE] = 0;

    Score_callback(sMessage);

    TEST_ASSERT_EQUAL(TRUE, bResetTimeAlarm);
}

void test_Score_updateScore_ShallIncrementScore(void)
{
    u8DailyScore = 0U;
    Score_updateDailyScore();
    TEST_ASSERT_EQUAL_UINT8(1U, u8DailyScore);
}

// Score execute shall increment the Score, when the flag for the state change was set
void test_Score_execute_ShallIncrementScoreAndResetTheFlag(void)
{
    u8DailyScore = 0U;
    bPomodoroSequenceCompleted = TRUE;
    bResetTimeAlarm = FALSE;

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    Score_execute();

    TEST_ASSERT_EQUAL(1U, u8DailyScore);
    TEST_ASSERT_EQUAL(FALSE, bPomodoroSequenceCompleted);
}

// Score execute shall reset the score when the alarm flag was set
void test_Score_execute_ShallResetScoreAndResetTheFlag(void)
{
    u8DailyScore = 5U;
    bPomodoroSequenceCompleted = FALSE;
    bResetTimeAlarm = TRUE;

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    Score_execute();

    TEST_ASSERT_EQUAL(0U, u8DailyScore);
    TEST_ASSERT_EQUAL(FALSE, bResetTimeAlarm);
}
