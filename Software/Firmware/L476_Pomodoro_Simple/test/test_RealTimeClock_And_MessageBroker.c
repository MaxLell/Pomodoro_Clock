#include "unity.h"

#include "RealTimeClock.h"
#include "mock_RealTimeClock_Hardware.h"
#include "MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

RealTimeClock_TimeAndDate_t tTimeAndDate = {0};

// The test subscribes to the TimeAndDate Topic, with a dummy callback that is created only here.
status_t dummy_messageCallback(MessageBroker_message_t msg)
{
    if (msg.eMsgTopic == E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE)
    {
        // This copies the data from the message into the global variable tTimeAndDate
        memcpy(&tTimeAndDate, msg.au8DataBytes, msg.u16DataSize);
    }
    return STATUS_OK;
}

/**
 * Integration Test: RealTimeClock_execute() with MessageBroker
 * - The RealTimeClock should publish the time and date via the MessageBroker
 *
 * Steps:
 * - The RealTimeClock is initialized
 * - Message Broker is initialized
 * - The Test subscribes to the TimeAndDate Topic, with a dummy callback that is created only here.
 * - The RealTimeClock is executed
 * - The TimeAndDate Data is parsed from the array within the dummy callback
 * - The TimeAndDate Data is compared to the expected data
 */
void test_RealTimeClock_execute_with_MessageBroker_should_PublishTheTimeAndDateViaTheMessageBroker(void)
{
    // Setup
    RealTimeClock_TimeAndDate_t tExpectedTimeAndDate = {0};
    tExpectedTimeAndDate.u8Hour = 12;
    tExpectedTimeAndDate.u8Minute = 34;
    tExpectedTimeAndDate.u8Second = 56;
    tExpectedTimeAndDate.u8Day = 11;
    tExpectedTimeAndDate.u8Month = 3;
    tExpectedTimeAndDate.u8Year = 23;

    // Message Broker is initialized
    MessageBroker_init(); // -> MessageBroker listens to all topics

    // The RealTimeClock is initialized -> RealTimeClock listens to the one second passed message
    RealTimeClock_init();

    // Send a message to the RealTimeClock, that one second has passed
    // -> So that the execute function actually does something
    MessageBroker_message_t tMessage = {0};
    tMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSED;
    MessageBroker_publish(tMessage);

    // The Test subscribes to the TimeAndDate Topic, with a dummy callback that is created only here.
    MessageBroker_subscribe(E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE, dummy_messageCallback);

    // Set the return value of the RealTimeClockHW_getTimeAndDate function
    RealTimeClockHW_getTimeAndDate_ExpectAndReturn(NULL, STATUS_OK);
    RealTimeClockHW_getTimeAndDate_IgnoreArg_in_pTimeAndDate();
    RealTimeClockHW_getTimeAndDate_ReturnThruPtr_in_pTimeAndDate(&tExpectedTimeAndDate);

    // The RealTimeClock is executed
    RealTimeClock_execute();

    // The TimeAndDate Data is parsed from the array within the dummy callback
    // The TimeAndDate Data is compared to the expected data
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Hour, tTimeAndDate.u8Hour);
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Minute, tTimeAndDate.u8Minute);
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Second, tTimeAndDate.u8Second);
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Day, tTimeAndDate.u8Day);
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Month, tTimeAndDate.u8Month);
    TEST_ASSERT_EQUAL(tExpectedTimeAndDate.u8Year, tTimeAndDate.u8Year);
}
