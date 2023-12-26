#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_MessageBroker.h"
#include "mock_PomodoroControl_StateFunctions.h"
#include "string.h"
#include "unity.h"

/********************************************************
 * extern static functions
 ********************************************************/

extern status_e PomodoroControl_MessageCallback(msg_t sMsg);

/********************************************************
 * extern private static variables
 ********************************************************/

extern PomodoroControl_internalStatus_t sInternalState;

/********************************************************
 * Implementation
 ********************************************************/

void setUp(void) {
  // Reset the internal state
  memset(&sInternalState, 0, sizeof(sInternalState));
}

void tearDown(void) {}

/**
 * Execute function -> State Transitions
 */

////////////////////////////////////////////////////
// Idle
////////////////////////////////////////////////////

// [Idle] ===============(MSG_ID_0200)=======> [Starting Sequence]
// [Idle] ===============()==================> [Idle]

////////////////////////////////////////////////////
// Starting Sequence
////////////////////////////////////////////////////

// [Starting Sequence] ===(StateFn-SUCCESS)==> [Worktime]
// [Starting Sequence] ===(StateFn-PENDING)==> [Starting Sequence]
// [Starting Sequence] ===(MSG_ID_0101)======> [Cancel Sequence]

////////////////////////////////////////////////////
// Worktime
////////////////////////////////////////////////////

// [Worktime] ============(StateFn-SUCCESS)==> [Warning]
// [Worktime] ============(StateFn-PENDING)==> [Worktime]
// [Worktime] ============(MSG_ID_0101)======> [Cancel Sequence]

////////////////////////////////////////////////////
// Warning
////////////////////////////////////////////////////

// [Warning] =============(StateFn-SUCCESS)==> [Breaktime]
// [Warning] =============(StateFn-PENDING)==> [Warning]
// [Warning] =============(MSG_ID_0101)======> [Cancel Sequence]

////////////////////////////////////////////////////
// Breaktime
////////////////////////////////////////////////////

// [Breaktime] ===========(MSG_ID_0101)======> [Cancel Sequence]
// [Breaktime] ===========(StateFn-SUCCESS)==> [Idle]
// [Breaktime] ===========(StateFn-PENDING)==> [Breaktime]

////////////////////////////////////////////////////
// Cancel Sequence
////////////////////////////////////////////////////

// [Cancel Sequence] ===(StateFn-SUCCESS)==> [Idle]
// [Cancel Sequence] ===(StateFn-PENDING)==> [Cancel Sequence]
// [Cancel Sequence] ===(MSG_ID_0102)======> [Prev. State: Idle]
// [Cancel Sequence] ===(MSG_ID_0102)======> [Prev. State: Starting Sequence]
// [Cancel Sequence] ===(MSG_ID_0102)======> [Prev. State: Worktime]
// [Cancel Sequence] ===(MSG_ID_0102)======> [Prev. State: Warning]
// [Cancel Sequence] ===(MSG_ID_0102)======> [Prev. State: Breaktime]