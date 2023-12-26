#include "Common.h"
#include "FSM.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

typedef enum {
  FSM_STATE_A = 0U,
  FSM_STATE_B,
  FSM_STATE_C,
  FSM_STATE_D,
  FSM_STATE_LAST
} FSM_state_e;

status_e StateRunDummyFn(uint16_t* const inout_u16State,
                         uint8_t* const inout_pData) {
  return STATUS_SUCCESS;
}

status_e StateRunDummyChangeStateFn(uint16_t* const inout_u16State,
                                    uint8_t* const inout_pData) {
  *inout_u16State = 12;
  return STATUS_SUCCESS;
}

status_e StateRunOnceDummyFn(const uint16_t* const in_u16FsmState,
                             uint8_t* const inout_pData) {
  return STATUS_SUCCESS;
}

FSM_StateCbs_t FSM_CbDummyOne[] = {
    [FSM_STATE_A] = {.pfnEntry = StateRunOnceDummyFn,
                     .pfnRun = StateRunDummyFn,
                     .pfnExit = StateRunOnceDummyFn},

    [FSM_STATE_B] = {.pfnEntry = StateRunOnceDummyFn,
                     .pfnRun = NULL,
                     .pfnExit = NULL},

    [FSM_STATE_C] = {.pfnEntry = NULL,
                     .pfnRun = StateRunDummyFn,
                     .pfnExit = NULL},

    [FSM_STATE_D] = {.pfnEntry = NULL,
                     .pfnRun = StateRunDummyChangeStateFn,
                     .pfnExit = NULL}};

void test_FSM_run_should_runAllThreeSubstates_when_RunFunctionReturnsSuccess(
    void) {
  uint8_t u8Data = 0U;
  status_e eStatus;

  uint16_t u16State = FSM_STATE_A;
  eStatus = FSM_runStateAction(FSM_CbDummyOne, &u16State, &u8Data);
  TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  u16State = FSM_STATE_B;
  eStatus = FSM_runStateAction(FSM_CbDummyOne, &u16State, &u8Data);
  TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);

  u16State = FSM_STATE_C;
  eStatus = FSM_runStateAction(FSM_CbDummyOne, &u16State, &u8Data);
  TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);
}

void test_FSM_run_RunFnShouldBeAbleToChangeState(void) {
  uint8_t u8Data = 0U;
  status_e eStatus;
  uint16_t u16State = FSM_STATE_D;
  eStatus = FSM_runStateAction(FSM_CbDummyOne, &u16State, &u8Data);
  TEST_ASSERT_EQUAL(STATUS_SUCCESS, eStatus);
  TEST_ASSERT_EQUAL(12, u16State);
}
