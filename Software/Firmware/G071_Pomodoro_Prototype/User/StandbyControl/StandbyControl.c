#include "StandbyControl.h"

#include "Common.h"
#include "MessageBroker.h"

/**********************************************************************
 * static local variables
 **********************************************************************/
STATIC BOOL bTriggerButtonPressed = FALSE;

/**********************************************************************
 * Message Callbacks
 **********************************************************************/
status_t StandbyControl_TriggerBtnPressedCB(msg_t in_sMessage) {
  bTriggerButtonPressed = TRUE;
  return STATUS_OK;
}

void StandbyControl_init() {
  status_t tStatus =
      MessageBroker_subscribe(MSG_ID_0100, StandbyControl_TriggerBtnPressedCB);
}

void StandbyControl_execute() {}
