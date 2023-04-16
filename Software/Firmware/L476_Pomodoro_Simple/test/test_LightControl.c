#include "unity.h"
#include "Common.h"
#include "Config.h"
#include "LightControl.h"
#include "mock_MessageBroker.h"
#include "mock_RgbLed.h"
#include "PomodoroFsm.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Extern static functions
 */
extern status_t LightControl_fillMinuteToColorArray(uint8_t in_u8CurrentMinute,
                                                    uint8_t in_u8WorktimeIntervalMin,
                                                    uint8_t in_u8BreaktimeIntervalMin,
                                                    uint8_t *inout_au8ColorArray);

extern status_t LightControl_removeColorsFromMinuteArray(uint8_t *inout_au8MinuteToColorArray,
                                                         uint8_t in_u8CurrentMinute);

extern status_t LightControl_fillLedToColorArray(uint8_t *in_au8MinuteToColorArray,
                                                 uint8_t *inout_au8LedToColorArray);

extern status_t LightControl_setLedsToColor(uint8_t *in_au8LedToColorArray);

/**
 * extern static variables
 */

extern uint8_t u8PFsmState;
extern uint8_t u8CurrentMinute;
extern uint8_t u8PFsmState;
extern uint8_t u8LightControlState;
extern BOOL bPomodoroSequenceInitialized;

/**
 * Helper functions
 */

void helper_printArray(uint8_t *in_au8Array, uint8_t in_u8ArraySize)
{
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
    {
        if (i < 10)
        {
            printf("%d  ", i);
        }
        else
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    for (uint8_t i = 0; i < in_u8ArraySize; i++)
    {
        printf("%d  ", in_au8Array[i]);
    }
    printf("\n");
}

void test_LightControl_fillMinuteToColorArray_Test4()
{
    // Test 4:
    // - Input: currentMinute = 17, worktimeIntervalMin = 50, breaktimeIntervalMin = 7
    // - Expected Output: [0...7] = W, [8...14] = B, [15...17] = 0, [18...59] = W
    uint8_t u8TestCurrentMinute = 17;
    uint8_t u8TestWorktimeIntervalMin = 50;
    uint8_t u8TestBreaktimeIntervalMin = 7;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    // Check the first 8 Minutes (Work Time)
    for (uint8_t u8Index = 0; u8Index < 7; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 7 Minutes (Break Time)
    for (uint8_t u8Index = 7; u8Index < 14; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_GREEN, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the next 3 Minutes (Off Time)
    for (uint8_t u8Index = 14; u8Index < 17; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8Index]);
    }

    // Check the last 42 Minutes (Work Time)
    for (uint8_t u8Index = 17; u8Index < MINUTES_IN_HOUR; u8Index++)
    {
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_RED, au8TestMinuteToColorArray[u8Index]);
    }
}

/*
 * Test 6:
 * - Input: currentMinute = 61, worktimeIntervalMin = 0, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test6()
{
    uint8_t u8TestCurrentMinute = 61;
    uint8_t u8TestWorktimeIntervalMin = 0;
    uint8_t u8TestBreaktimeIntervalMin = 0;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 7:
 * - Input: currentMinute = 0, worktimeIntervalMin = 61, breaktimeIntervalMin = 0
 * - Expected Output: [0...59] = 0; returns a Status Invalid Argument
 */
void test_LightControl_fillMinuteToColorArray_Test7()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 61;
    uint8_t u8TestBreaktimeIntervalMin = 0;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 8:
 * - Input: currentMinute = 0, worktimeIntervalMin = 10, breaktimeIntervalMin = 60
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test8()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 10;
    uint8_t u8TestBreaktimeIntervalMin = 60;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}

/*
 * Test 9:
 * - Input: currentMinute = 0, worktimeIntervalMin = 67, breaktimeIntervalMin = 10
 * - Expected Output: [0...59] = 0; returns a Status Error Code
 */
void test_LightControl_fillMinuteToColorArray_Test9()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 67;
    uint8_t u8TestBreaktimeIntervalMin = 10;
    uint8_t au8TestMinuteToColorArray[60] = {0};

    uint8_t u8Status = LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, u8Status);
}
/**
 * Tests for LightControl_fillLedToColorArray():
 * Test 11:
 * - Input [0...30] = W, [30...50] = B, [50...59] = 0
 * - Output [0...11] = W, [12...20] = B, [21...23] = 0
 */
void test_LightControl_fillLedToColorArray_Test11()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightControl_fillLedToColorArray(au8TestMinuteToColorArray, au8TestLedToColorArray);

    float u8LedsPerMinute = (float)TOTAL_LEDS / (float)MINUTES_IN_HOUR;

    for (float i = 0; i < MINUTES_IN_HOUR; i++)
    {
        uint8_t index = (uint8_t)(i * u8LedsPerMinute);
        TEST_ASSERT_EQUAL(au8TestMinuteToColorArray[(uint8_t)i], au8TestLedToColorArray[index]);
    }
}

/**
 * Tests for LightControl_removeColorsFromMinuteArray():
 * Test 12:
 * The input is a default time array with the spec as it is shown below
 * The remove function shall take out the current minute from the array
 */
void test_LightControl_removeColorsFromMinuteArray_Test12()
{
    uint8_t u8TestCurrentMinute = 0;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);

    // try another minute
    u8TestCurrentMinute = 12;
    LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, u8TestCurrentMinute);
    TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[u8TestCurrentMinute]);
}

/**
 * Tests for LightControl_removeColorsFromMinuteArray():
 * Test 13:
 * Remove all colors from the array
 */

void test_LightControl_removeColorsFromMinuteArray_Test13()
{
    uint8_t u8TestCurrentMinute = 25;
    uint8_t u8TestWorktimeIntervalMin = 30;
    uint8_t u8TestBreaktimeIntervalMin = 20;
    uint8_t au8TestMinuteToColorArray[MINUTES_IN_HOUR] = {0};
    uint8_t au8TestLedToColorArray[TOTAL_LEDS] = {0};

    LightControl_fillMinuteToColorArray(
        u8TestCurrentMinute,
        u8TestWorktimeIntervalMin,
        u8TestBreaktimeIntervalMin,
        au8TestMinuteToColorArray);

    for (uint8_t i = 0; i < MINUTES_IN_HOUR; i++)
    {
        LightControl_removeColorsFromMinuteArray(au8TestMinuteToColorArray, i);
        TEST_ASSERT_EQUAL(LIGHTCONTROL_LED_OFF, au8TestMinuteToColorArray[i]);
    }
}

/**
 * Tests for LightControl_init()
 * - It shall subscribe to the current time topic
 * - It shall subscribe to the PFSM State Change topic
 */
void test_LightControl_init_should_SubscribeToMessageBrokerTopics()
{
    // Subscribe to the current time topic
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE,
        NULL,
        STATUS_OK);
    MessageBroker_subscribe_IgnoreArg_in_p32FunctionCallback();

    // Subscribe to the PFSM State Change topic
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED,
        NULL,
        STATUS_OK);
    MessageBroker_subscribe_IgnoreArg_in_p32FunctionCallback();
    LightControl_init();
}

/**
 * Tests for LightControl_init()
 * - It shall set the internal Pfsm state to Idle
 * - It shall set the internal LightControl State to Idle
 */
void test_LightControl_init_should_SetInternalPfsmAndLightControlStateToIdle()
{
    // Subscribe to the current time topic
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE,
        NULL,
        STATUS_OK);
    MessageBroker_subscribe_IgnoreArg_in_p32FunctionCallback();

    // Subscribe to the PFSM State Change topic
    MessageBroker_subscribe_ExpectAndReturn(
        E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED,
        NULL,
        STATUS_OK);
    MessageBroker_subscribe_IgnoreArg_in_p32FunctionCallback();

    LightControl_init();

    TEST_ASSERT_EQUAL(E_PFSM_STATE_IDLE, u8PFsmState);
    TEST_ASSERT_EQUAL(E_LCTRL_STATE_IDLE, u8LightControlState);
}

/**
 * Tests for LightControl_messageBrokerCallback()
 * - should parse the current time and set the current minute
 */

extern status_t LightControl_messageBrokerCallback(MessageBroker_message_t in_tMessage);
void test_LightControl_messageBrokerCallback_should_ParseCurrentTimeAndSetCurrentMinute()
{
    MessageBroker_message_t tTestMessage;
    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;
    uint8_t au8TestTime[2] = {0, 50};
    tTestMessage.au8DataBytes = au8TestTime;
    tTestMessage.u16DataSize = 2;
    LightControl_messageBrokerCallback(tTestMessage);

    TEST_ASSERT_EQUAL(50, u8CurrentMinute);
}

/**
 * Tests for LightControl_messageBrokerCallback()
 * - should parse the PFSM state
 */

void test_LightControl_messageBrokerCallback_should_ParsePFSMState()
{
    u8PFsmState = 0;
    MessageBroker_message_t tTestMessage;
    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED;
    uint8_t au8TestPFSMStates[2] = {E_PFSM_STATE_SEEKING_ATTENTION, E_PFSM_STATE_IDLE};
    tTestMessage.au8DataBytes = au8TestPFSMStates;
    tTestMessage.u16DataSize = 2;
    LightControl_messageBrokerCallback(tTestMessage);

    TEST_ASSERT_EQUAL(E_PFSM_STATE_SEEKING_ATTENTION, u8PFsmState);
}

/**
 * Tests for LightControl_messageBrokerCallback()
 * - should return STATUS_OK when everything is fine
 */
void test_LightControl_messageBrokerCallback_should_ReturnStatusOk_when_EverythingIsFine()
{
    MessageBroker_message_t tTestMessage;
    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE;
    uint8_t au8TestTime[2] = {0, 50};
    tTestMessage.au8DataBytes = au8TestTime;
    tTestMessage.u16DataSize = 2;
    TEST_ASSERT_EQUAL(STATUS_OK, LightControl_messageBrokerCallback(tTestMessage));

    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED;
    uint8_t au8TestPFSMStates[2] = {E_PFSM_STATE_SEEKING_ATTENTION, E_PFSM_STATE_IDLE};
    tTestMessage.au8DataBytes = au8TestPFSMStates;
    tTestMessage.u16DataSize = 2;
    TEST_ASSERT_EQUAL(STATUS_OK, LightControl_messageBrokerCallback(tTestMessage));
}

/**
 * Tests for LightControl_messageBrokerCallback()
 * - should return STATUS_INVALID_ARG when the message topic is not supported
 */
void test_LightControl_messageBrokerCallback_should_ReturnStatusInvalidArg_when_MessageTopicIsNotSupported()
{
    MessageBroker_message_t tTestMessage;
    tTestMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED + 1;
    uint8_t au8TestTime[2] = {0, 50};
    tTestMessage.au8DataBytes = au8TestTime;
    tTestMessage.u16DataSize = 2;
    TEST_ASSERT_EQUAL(STATUS_INVALID_ARG, LightControl_messageBrokerCallback(tTestMessage));
}

/**
 * Tests for LightControl_execute()
 * - should return STATUS_OK when everything is fine
 */

void test_LightControl_execute_should_ReturnStatusOk_when_EverythingIsFine()
{
    TEST_ASSERT_EQUAL(STATUS_OK, LightControl_execute());
}

/**
 * Tests for LightControl_execute()
 * - Should transition from Idle to SeekingAttention when PFSM changes to SeekingAttention
 */

void test_LightControl_execute_should_TransitionFromIdleToSeekingAttention_when_PFSMChangesToSeekingAttention()
{
    u8PFsmState = E_PFSM_STATE_IDLE;
    u8LightControlState = E_LCTRL_STATE_IDLE;
    LightControl_execute();
    TEST_ASSERT_EQUAL(E_LCTRL_STATE_IDLE, u8LightControlState);

    u8PFsmState = E_PFSM_STATE_SEEKING_ATTENTION;
    LightControl_execute();
    TEST_ASSERT_EQUAL(E_LCTRL_STATE_SEEKING_ATTENTION, u8LightControlState);
}

/**
 * Tests for LightControl_execute()
 * - Should transition from SeekingAttention to Pomodoro Worktime when PFSM changes to Worktime
 */

void test_LightControl_execute_should_TransitionFromSeekingAttentionToPomodoroWorktime_when_PFSMChangesToWorktime()
{
    u8PFsmState = E_PFSM_STATE_SEEKING_ATTENTION;
    u8LightControlState = E_LCTRL_STATE_SEEKING_ATTENTION;
    LightControl_execute();
    TEST_ASSERT_EQUAL(E_LCTRL_STATE_SEEKING_ATTENTION, u8LightControlState);

    u8PFsmState = E_PFSM_STATE_WORKTIME;
    LightControl_execute();
    TEST_ASSERT_EQUAL(E_LCTRL_STATE_POMODORO_WORKTIME, u8LightControlState);
}

/**
 * Tests for LightControl_execute()
 * - When in Pomodoro Worktime state, the Array should be initialized once
 */
