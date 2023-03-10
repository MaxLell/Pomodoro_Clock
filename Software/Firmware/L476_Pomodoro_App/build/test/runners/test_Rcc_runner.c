/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Rcc_Init_should_EnableHSIClock(void);
extern void test_Rcc_Init_should_WaitUntilHSIClockIsStable(void);
extern void test_Rcc_Init_should_SetHSIAsMainClockSource(void);
extern void test_Rcc_Init_should_SetUpFlash(void);
extern void test_Rcc_Init_should_SetUpThePeripheralClockDeviders(void);
extern void test_Rcc_Init_should_EnableMcoOfTheSysclock(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
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
  UnityBegin("test_Rcc.c");
  run_test(test_Rcc_Init_should_EnableHSIClock, "test_Rcc_Init_should_EnableHSIClock", 21);
  run_test(test_Rcc_Init_should_WaitUntilHSIClockIsStable, "test_Rcc_Init_should_WaitUntilHSIClockIsStable", 32);
  run_test(test_Rcc_Init_should_SetHSIAsMainClockSource, "test_Rcc_Init_should_SetHSIAsMainClockSource", 51);
  run_test(test_Rcc_Init_should_SetUpFlash, "test_Rcc_Init_should_SetUpFlash", 64);
  run_test(test_Rcc_Init_should_SetUpThePeripheralClockDeviders, "test_Rcc_Init_should_SetUpThePeripheralClockDeviders", 77);
  run_test(test_Rcc_Init_should_EnableMcoOfTheSysclock, "test_Rcc_Init_should_EnableMcoOfTheSysclock", 94);

  return UnityEnd();
}
