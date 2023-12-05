#include "MessageBroker.h"
#include "StandbyControl.h"
#include "mock_CountdownTimer.h"
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

  Countdown_initTimer_Ignore();

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

  Countdown_initTimer_Ignore();
  Countdown_getTimerStatus_IgnoreAndReturn(TIMER_NOT_EXPIRED);

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

/**
 * StandbyControl_Idle_state shall start a timer with a random timespan between
 * 17 sec. (But only when the timer was not set before)
 */

/**
 * Standby Control shall change its internal state to
 * StandbyControl_SeekingAttention state when the timer is expired
 */