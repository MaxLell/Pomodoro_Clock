#include "unity.h"

#include "MessageBroker.h"

void setUp(void)
{
    /*
    Reset the callback arrays with the init function
    */

    MessageBroker_init();
}

void tearDown(void)
{
}

void test_MessageBroker_should_xxx()
{
    TEST_IGNORE_MESSAGE("Implement me ya bloody bastard!!!");
}

/**
 * Message Broker acceptance tests
 * MessageBroker_subscribe()
 * - A Module can register its callback in its respective callback array
 * - If there is no callback array, that corresponds to this ID, the system fails loud and noisy
 * - The high watermark of the callback array is incremented
 *
 * MessageBroker_publish()
 * - A new Message can be added to the queue
 * - When too many messages are added to the queue, then the system fails loud and noisy
 *
 * MessageBroker_exec()
 * - From the message the ID can be captured
 * - From the ID a Callback Array can be identified - if this is not possible fail loud and noisy
 * - The callback funcions are itereated over
 */