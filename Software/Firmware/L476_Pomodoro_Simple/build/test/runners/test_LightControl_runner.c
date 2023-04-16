/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_MessageBroker.h"
#include "mock_RgbLed.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_LightControl_fillMinuteToColorArray_Test4();
extern void test_LightControl_fillMinuteToColorArray_Test6();
extern void test_LightControl_fillMinuteToColorArray_Test7();
extern void test_LightControl_fillMinuteToColorArray_Test8();
extern void test_LightControl_fillMinuteToColorArray_Test9();
extern void test_LightControl_fillLedToColorArray_Test11();
extern void test_LightControl_removeColorsFromMinuteArray_Test12();
extern void test_LightControl_removeColorsFromMinuteArray_Test13();
extern void test_LightControl_init_should_SubscribeToMessageBrokerTopics();
extern void test_LightControl_init_should_SetInternalPfsmAndLightControlStateToIdle();
extern void test_LightControl_messageBrokerCallback_should_ParseCurrentTimeAndSetCurrentMinute();
extern void test_LightControl_messageBrokerCallback_should_ParsePFSMState();
extern void test_LightControl_messageBrokerCallback_should_ReturnStatusOk_when_EverythingIsFine();
extern void test_LightControl_messageBrokerCallback_should_ReturnStatusInvalidArg_when_MessageTopicIsNotSupported();
extern void test_LightControl_execute_should_ReturnStatusOk_when_EverythingIsFine();
extern void test_LightControl_execute_should_TransitionFromIdleToSeekingAttention_when_PFSMChangesToSeekingAttention();
extern void test_LightControl_execute_should_TransitionFromSeekingAttentionToPomodoroWorktime_when_PFSMChangesToWorktime();


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_MessageBroker_Init();
  mock_RgbLed_Init();
}
static void CMock_Verify(void)
{
  mock_MessageBroker_Verify();
  mock_RgbLed_Verify();
}
static void CMock_Destroy(void)
{
  mock_MessageBroker_Destroy();
  mock_RgbLed_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_LightControl.c");
  run_test(test_LightControl_fillMinuteToColorArray_Test4, "test_LightControl_fillMinuteToColorArray_Test4", 68);
  run_test(test_LightControl_fillMinuteToColorArray_Test6, "test_LightControl_fillMinuteToColorArray_Test6", 114);
  run_test(test_LightControl_fillMinuteToColorArray_Test7, "test_LightControl_fillMinuteToColorArray_Test7", 135);
  run_test(test_LightControl_fillMinuteToColorArray_Test8, "test_LightControl_fillMinuteToColorArray_Test8", 156);
  run_test(test_LightControl_fillMinuteToColorArray_Test9, "test_LightControl_fillMinuteToColorArray_Test9", 177);
  run_test(test_LightControl_fillLedToColorArray_Test11, "test_LightControl_fillLedToColorArray_Test11", 198);
  run_test(test_LightControl_removeColorsFromMinuteArray_Test12, "test_LightControl_removeColorsFromMinuteArray_Test12", 229);
  run_test(test_LightControl_removeColorsFromMinuteArray_Test13, "test_LightControl_removeColorsFromMinuteArray_Test13", 258);
  run_test(test_LightControl_init_should_SubscribeToMessageBrokerTopics, "test_LightControl_init_should_SubscribeToMessageBrokerTopics", 284);
  run_test(test_LightControl_init_should_SetInternalPfsmAndLightControlStateToIdle, "test_LightControl_init_should_SetInternalPfsmAndLightControlStateToIdle", 307);
  run_test(test_LightControl_messageBrokerCallback_should_ParseCurrentTimeAndSetCurrentMinute, "test_LightControl_messageBrokerCallback_should_ParseCurrentTimeAndSetCurrentMinute", 335);
  run_test(test_LightControl_messageBrokerCallback_should_ParsePFSMState, "test_LightControl_messageBrokerCallback_should_ParsePFSMState", 352);
  run_test(test_LightControl_messageBrokerCallback_should_ReturnStatusOk_when_EverythingIsFine, "test_LightControl_messageBrokerCallback_should_ReturnStatusOk_when_EverythingIsFine", 369);
  run_test(test_LightControl_messageBrokerCallback_should_ReturnStatusInvalidArg_when_MessageTopicIsNotSupported, "test_LightControl_messageBrokerCallback_should_ReturnStatusInvalidArg_when_MessageTopicIsNotSupported", 389);
  run_test(test_LightControl_execute_should_ReturnStatusOk_when_EverythingIsFine, "test_LightControl_execute_should_ReturnStatusOk_when_EverythingIsFine", 404);
  run_test(test_LightControl_execute_should_TransitionFromIdleToSeekingAttention_when_PFSMChangesToSeekingAttention, "test_LightControl_execute_should_TransitionFromIdleToSeekingAttention_when_PFSMChangesToSeekingAttention", 414);
  run_test(test_LightControl_execute_should_TransitionFromSeekingAttentionToPomodoroWorktime_when_PFSMChangesToWorktime, "test_LightControl_execute_should_TransitionFromSeekingAttentionToPomodoroWorktime_when_PFSMChangesToWorktime", 431);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
