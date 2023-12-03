#include "unity.h"

#include "StandbyControl.h"
#include "MessageBroker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_StandbyControl_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement StandbyControl");
}

/**
 * Standby Trigger Button Single Click callback is called, when a MSG_0100 is published
 * Publish the Message
 *
 * Check whether the internal flag of the Module was set )
 */

void test_StandbyTriggerButtonSinglePress_should_SetItsInternalFlag_when_AButtonPressedEventHappened()
{
}

/**
 * Standby clears the Triggered Button event at the end of each iteration, even if there was no internal reaction to the Button
 * (As it always listens?)
 */

void test_Standby_init_should_subscribeToMsgId0100(void)
{
}
