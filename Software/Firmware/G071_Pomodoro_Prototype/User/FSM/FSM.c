#include "FSM.h"

typedef enum {
  E_FSM_ENTRY = 0U,
  E_FSM_RUN,
  E_FSM_EXIT,
} FSM_stateCondition_e;

STATIC uint8_t u8LocalInternalState = E_FSM_ENTRY;
STATIC uint16_t u16BufferedState;

status_e FSM_runStateAction(const FSM_StateCbs_t* const psFsmCallbacks,
                         uint16_t* const inout_u16State,
                         uint8_t* const inout_pData) {
  {  // Input checks
     // Null Pointer Checks on the input Arguments

    // No checks on the FN Pointers required, as they may be NULL and this
    // behaviour is expected
  }

  status_e eReturnStatus = STATUS_ERROR;
  static BOOL bRanOnce = FALSE;
  u16BufferedState = *inout_u16State;

  switch (u8LocalInternalState) {
    case E_FSM_ENTRY: {
      // Run the provided function (if not null)
      if (*psFsmCallbacks[u16BufferedState].pfnEntry == NULL) {
        // increment the local state
        u8LocalInternalState++;
      } else {
        // execute the Function
        status_e eStatus = (*psFsmCallbacks[u16BufferedState].pfnEntry)(
            inout_u16State, inout_pData);

        // Error Checks
        ASSERT_MSG(!(eStatus != STATUS_SUCCESS),
                   "Entry Function must return STATUS_SUCCESS but returned "
                   "instead: %d",
                   eStatus);

        // if the Cb's return statement is Success -> then incremnet the
        // localInternalState
        if (eStatus == STATUS_SUCCESS) {
          u8LocalInternalState++;
        } else {  // A return Statement other then Success is not allowed
          eReturnStatus = STATUS_ERROR;
          break;
        }
      }
    }

    case E_FSM_RUN: {
      // Set the eReturnStatus to Pending
      eReturnStatus = STATUS_PENDING;

      // Execute the function when not NULL
      if (*psFsmCallbacks[*inout_u16State].pfnRun == NULL) {
        u8LocalInternalState++;
      } else {
        // Run the callback

        status_e eStatus = (*psFsmCallbacks[*inout_u16State].pfnRun)(
            inout_u16State, inout_pData);

        // Check return statements
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "Run Function returned error");

        // if the status is success move on
        if (eStatus == STATUS_SUCCESS) {
          u8LocalInternalState++;
        }  // if the status is pending -> stay in the Run State
        else {
          break;
        }
      }
    }

    case E_FSM_EXIT: {
      // Execute the function when not NULL
      // if return statement is success -> move internal State to Entry State

      if (*psFsmCallbacks[u16BufferedState].pfnExit == NULL) {
        u8LocalInternalState = E_FSM_ENTRY;
        eReturnStatus = STATUS_SUCCESS;
      } else {
        // Run the callback
        status_e eStatus = (*psFsmCallbacks[u16BufferedState].pfnExit)(
            inout_u16State, inout_pData);

        // Check return statements
        ASSERT_MSG(!(eStatus == STATUS_ERROR), "Exit Function returned error");

        // if the status is success move on
        if (eStatus == STATUS_SUCCESS) {
          u8LocalInternalState = E_FSM_ENTRY;
          eReturnStatus = STATUS_SUCCESS;

          // Reset the RanOnce Flag

        } else {
          // if the status is pending -> stay in the Exit State
          eReturnStatus = STATUS_PENDING;
        }
      }
    } break;

    default:
      ASSERT_MSG(FALSE, "Invalid State");
      eReturnStatus = STATUS_ERROR;
      break;
  }
  return eReturnStatus;
}

void FSM_getNextState(const FSM_Config_t* const in_psFsmConfig,
                      int16_t* const inout_i16State,
                      const uint16_t in_u16Event) {
  {  // Input Checks
    ASSERT_MSG(!(in_psFsmConfig == NULL), "in_psFsmConfig is NULL");
    ASSERT_MSG(!(inout_i16State == NULL), "inout_i16State is NULL");
    ASSERT_MSG(!(in_psFsmConfig->psaTransitionMatrix == NULL),
               "in_psFsmConfig->psaTransitionMatrix is NULL");
    ASSERT_MSG(!(in_psFsmConfig->psStateCbs == NULL),
               "in_psFsmConfig->psStateCbs is NULL");
    ASSERT_MSG(!(*inout_i16State >= in_psFsmConfig->NUMBER_OF_STATES),
               "in_u16CurrentState is out of bounds");
    ASSERT_MSG(!(in_u16Event >= in_psFsmConfig->NUMBER_OF_EVENTS),
               "in_u16Event is out of bounds");
  }

  // Approach taken from https://stackoverflow.com/a/54103595
  *inout_i16State =
      *(in_psFsmConfig->psaTransitionMatrix +
        *inout_i16State * in_psFsmConfig->NUMBER_OF_EVENTS + in_u16Event);
}
