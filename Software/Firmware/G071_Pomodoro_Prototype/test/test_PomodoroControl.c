#include "PomodoroControl.h"
#include "PomodoroControl_Datatypes.h"
#include "mock_MessageBroker.h"
#include "mock_PomodoroControl_StateFunctions.h"
#include "unity.h"

/********************************************************
 * extern static functions
 ********************************************************/

extern status_t PomodoroControl_MessageCallback(msg_t sMsg);

/********************************************************
 * extern private static variables
 ********************************************************/

/********************************************************
 * Implementation
 ********************************************************/

void setUp(void) {}

void tearDown(void) {}

/**
 * Execute function -> State Transitions
 */

// [Idle] ================(MSG_ID_0200)======> [Starting Sequence]

// [Starting Sequence] ===(StateFn-SUCCESS)==> [Worktime]

// [Worktime] ============(StateFn-SUCCESS)==> [Warning]

// [Warning] =============(StateFn-SUCCESS)==> [Breaktime]

// [Starting Sequence] ===(MSG_ID_0101)======> [Cancel Sequence]

// [Worktime] ============(MSG_ID_0101)======> [Cancel Sequence]

// [Warning] =============(MSG_ID_0101)======> [Cancel Sequence]

// [Breaktime] ===========(MSG_ID_0101)======> [Cancel Sequence]

/**
 * Idle function
 * - Subscribe to MSG_ID_0200
 * - Subscribe to MSG_ID_0101
 * - Set the internal state to Idle
 */

/**
 * Message Callback
 * - set the respective internal status flags (TBDs)
 */