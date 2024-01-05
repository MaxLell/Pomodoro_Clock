#include "Button.h"

#include "BlinkyLed.h"
#include "MessageBroker.h"

static BOOL bButtonState = FALSE;

void Button_wasPressed(BOOL* pBButtonWasPressed) {
  *pBButtonWasPressed = bButtonState;

  // Reset the button state after reading it
  bButtonState = FALSE;
}

void Button_ISR(void) {
  bButtonState = TRUE;
}

void Button_execute(void) {
  BOOL bButtonWasPressed;
  Button_wasPressed(&bButtonWasPressed);
  if (bButtonWasPressed) {
    msg_t sMsg;
    sMsg.eMsgId = MSG_ID_0100;
    sMsg.u16DataSize = 0;
    sMsg.au8DataBytes = NULL;
    status_e tStatus = MessageBroker_publish(&sMsg);
    ASSERT_MSG(!(tStatus != STATUS_SUCCESS),
               "MessageBroker_publish() failed with error code: %d", tStatus);
  }
}
