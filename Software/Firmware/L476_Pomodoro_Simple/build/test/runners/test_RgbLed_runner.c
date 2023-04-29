/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_MessageBroker.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_RgbLed_Init_ShallSubscribeToTopic(void);
extern void test_RgbLed_Init_ShallClearRgbLedArray(void);
extern void test_RgbLed_Init_ShallClearEncodedColorsArray(void);
extern void test_RgbLed_Init_ShallSetNewEntryFlagToFalse(void);
extern void test_RgbLed_Callback_ShallCopyIncomingArrayIntoEncodedColorsArray(void);
extern void test_RgbLed_Callback_ShallSetNewEntryFlagToTrue(void);
extern void test_RgbLed_DecodeColors_ShallMapEncodedColorsToRgbColors(void);
extern void test_RgbLed_SetLed_should_SetOneLed(void);
extern void test_RgbLed_CreatePwmArray_should_CreatePwmArray(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_MessageBroker_Init();
}
static void CMock_Verify(void)
{
  mock_MessageBroker_Verify();
}
static void CMock_Destroy(void)
{
  mock_MessageBroker_Destroy();
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
  UnityBegin("test_RgbLed.c");
  run_test(test_RgbLed_Init_ShallSubscribeToTopic, "test_RgbLed_Init_ShallSubscribeToTopic", 38);
  run_test(test_RgbLed_Init_ShallClearRgbLedArray, "test_RgbLed_Init_ShallClearRgbLedArray", 48);
  run_test(test_RgbLed_Init_ShallClearEncodedColorsArray, "test_RgbLed_Init_ShallClearEncodedColorsArray", 72);
  run_test(test_RgbLed_Init_ShallSetNewEntryFlagToFalse, "test_RgbLed_Init_ShallSetNewEntryFlagToFalse", 90);
  run_test(test_RgbLed_Callback_ShallCopyIncomingArrayIntoEncodedColorsArray, "test_RgbLed_Callback_ShallCopyIncomingArrayIntoEncodedColorsArray", 101);
  run_test(test_RgbLed_Callback_ShallSetNewEntryFlagToTrue, "test_RgbLed_Callback_ShallSetNewEntryFlagToTrue", 123);
  run_test(test_RgbLed_DecodeColors_ShallMapEncodedColorsToRgbColors, "test_RgbLed_DecodeColors_ShallMapEncodedColorsToRgbColors", 136);
  run_test(test_RgbLed_SetLed_should_SetOneLed, "test_RgbLed_SetLed_should_SetOneLed", 169);
  run_test(test_RgbLed_CreatePwmArray_should_CreatePwmArray, "test_RgbLed_CreatePwmArray_should_CreatePwmArray", 239);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}