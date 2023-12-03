#include "MessageBroker.h"
#include "StandbyControl.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

/**
 * Standby Trigger Button Single Click callback is called, when a MSG_0100 is
 * published Publish the Message
 *
 * Check whether the internal flag of the Module was set )
 */
extern BOOL bTriggerButtonPressed;
void test_StandbyTriggerButtonSinglePress_should_SetItsInternalFlag_when_AButtonPressedEventHappened() {
  // Arrange
  msg_t sMsg;
  sMsg.eMsgId = MSG_ID_0100;
  sMsg.u16DataSize = 0;
  sMsg.au8DataBytes = NULL;

  TEST_ASSERT_EQUAL(FALSE, bTriggerButtonPressed);

  // Act
  MessageBroker_init();
  StandbyControl_init();

  // Dummy pulbish
  MessageBroker_publish(sMsg);

  // Assert
  TEST_ASSERT_EQUAL(TRUE, bTriggerButtonPressed);
}

/**
 * StandbyControl execute clears the Triggered Button event at the end of each
 * iteration, even if there was no internal reaction to the Button (As it always
 * listens?)
 */

void test_StandbyControl_execute_should_ClearItsInternalTheTriggerButtonFlag() {
  // Arrange
  msg_t sMsg;
  sMsg.eMsgId = MSG_ID_0100;
  sMsg.u16DataSize = 0;
  sMsg.au8DataBytes = NULL;
  bTriggerButtonPressed = FALSE;

  // Act
  MessageBroker_init();
  StandbyControl_init();

  // Dummy pulbish
  MessageBroker_publish(sMsg);

  // Assert
  TEST_ASSERT_EQUAL(TRUE, bTriggerButtonPressed);

  // Act
  StandbyControl_execute();

  // Assert
  TEST_ASSERT_EQUAL(FALSE, bTriggerButtonPressed);
}
