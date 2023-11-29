#include "unity.h"

#include "RealTimeClock.h"
#include "mock_RealTimeClock_Hardware.h"
#include "mock_MessageBroker.h"
#include "string.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * Test: RealTimeClock_publishTimeAndDate()
 * - should publish the provided time and date via the Message Broker
 */
extern status_t RealTimeClock_publishTimeAndDate(RealTimeClock_TimeAndDate_t in_sTimeAndDate);
void test_RealTimeClock_publishTimeAndDate_should_PublishTheProvidedTimeAndDateViaTheMessageBroker(void)
{
    // Setup
    RealTimeClock_TimeAndDate_t tTimeAndDate = {0};
    tTimeAndDate.u8Hour = 12;
    tTimeAndDate.u8Minute = 34;
    tTimeAndDate.u8Second = 56;
    tTimeAndDate.u8Day = 1;
    tTimeAndDate.u8Month = 2;
    tTimeAndDate.u8Year = 3;

    MessageBroker_message_t tMessage = {0};
    tMessage.eMsgTopic = E_TOPIC_TIME_AND_DATE;
    tMessage.u16DataSize = TIME_AND_DATE_DATA_SIZE_BYTES;
    tMessage.au8DataBytes = (uint8_t *)&tTimeAndDate;

    MessageBroker_publish_IgnoreAndReturn(STATUS_OK);

    // Execute
    status_t tStatus = RealTimeClock_publishTimeAndDate(tTimeAndDate);

    // Verify
    TEST_ASSERT_EQUAL(STATUS_OK, tStatus);
}

/**
 * Test: RealTimeClock_init()
 * - should subscribe to the E_TOPIC_ONE_SECOND_PASSED topic
 */

void test_RealTimeClock_init_should_SubscribeToTheE_MESSAGE_BROKER_TOPIC_ONC_SECOND_PASSEDTopic(void)
{
    // Setup
    MessageBroker_subscribe_IgnoreAndReturn(STATUS_OK);

    // Execute
    RealTimeClock_init();

    // Verify
}