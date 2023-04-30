/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_BlinkyLed.h"
#include "mock_StopWatch.h"
#include "mock_Button.h"
#include "mock_RealTimeClock.h"
#include "mock_MessageBroker.h"
#include "mock_Buzzer.h"
#include "mock_LightEffects.h"
#include "mock_PomodoroFsm.h"
#include "mock_RgbLed.h"
#include "mock_Score.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Executer_init_ShouldInitializeAllModules(void);
extern void test_Executer_execute_should_ExecuteAllModules(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_BlinkyLed_Init();
  mock_StopWatch_Init();
  mock_Button_Init();
  mock_RealTimeClock_Init();
  mock_MessageBroker_Init();
  mock_Buzzer_Init();
  mock_LightEffects_Init();
  mock_PomodoroFsm_Init();
  mock_RgbLed_Init();
  mock_Score_Init();
}
static void CMock_Verify(void)
{
  mock_BlinkyLed_Verify();
  mock_StopWatch_Verify();
  mock_Button_Verify();
  mock_RealTimeClock_Verify();
  mock_MessageBroker_Verify();
  mock_Buzzer_Verify();
  mock_LightEffects_Verify();
  mock_PomodoroFsm_Verify();
  mock_RgbLed_Verify();
  mock_Score_Verify();
}
static void CMock_Destroy(void)
{
  mock_BlinkyLed_Destroy();
  mock_StopWatch_Destroy();
  mock_Button_Destroy();
  mock_RealTimeClock_Destroy();
  mock_MessageBroker_Destroy();
  mock_Buzzer_Destroy();
  mock_LightEffects_Destroy();
  mock_PomodoroFsm_Destroy();
  mock_RgbLed_Destroy();
  mock_Score_Destroy();
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
  UnityBegin("test_Executer.c");
  run_test(test_Executer_init_ShouldInitializeAllModules, "test_Executer_init_ShouldInitializeAllModules", 23);
  run_test(test_Executer_execute_should_ExecuteAllModules, "test_Executer_execute_should_ExecuteAllModules", 37);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
