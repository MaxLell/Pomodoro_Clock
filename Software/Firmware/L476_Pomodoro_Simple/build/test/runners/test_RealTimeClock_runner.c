/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_RealTimeClock_Hardware.h"
#include "mock_MessageBroker.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_RealTimeClock_publishTimeAndDate_should_PublishTheProvidedTimeAndDateViaTheMessageBroker(void);
extern void test_RealTimeClock_init_should_SubscribeToTheE_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSEDTopic(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_RealTimeClock_Hardware_Init();
  mock_MessageBroker_Init();
}
static void CMock_Verify(void)
{
  mock_RealTimeClock_Hardware_Verify();
  mock_MessageBroker_Verify();
}
static void CMock_Destroy(void)
{
  mock_RealTimeClock_Hardware_Destroy();
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
  UnityBegin("test_RealTimeClock.c");
  run_test(test_RealTimeClock_publishTimeAndDate_should_PublishTheProvidedTimeAndDateViaTheMessageBroker, "test_RealTimeClock_publishTimeAndDate_should_PublishTheProvidedTimeAndDateViaTheMessageBroker", 21);
  run_test(test_RealTimeClock_init_should_SubscribeToTheE_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSEDTopic, "test_RealTimeClock_init_should_SubscribeToTheE_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSEDTopic", 51);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
