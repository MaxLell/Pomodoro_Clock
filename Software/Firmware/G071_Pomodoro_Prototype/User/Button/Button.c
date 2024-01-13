#include "Button.h"
#include "Button_Hardware.h"

#include "MessageBroker.h"

static BOOL bButtonState = FALSE;

void Button_wasPressed(BOOL *pBButtonWasPressed)
{
    *pBButtonWasPressed = bButtonState;

    // Reset the button state after reading it
    bButtonState = FALSE;
}

void Button_ISR(void)
{
    bButtonState = TRUE;
}

/**
 * Taken from https://web.archive.org/web/20230223060958/http://www.ganssle.com/debouncing-pt2.htm
 */
void Button_Debounce(BOOL *out_pbDebouncedButtonWasPressed)
{
    static uint16_t u16State = 0;
    u16State = (u16State << 1) | !Button_getState() | 0xe000;
    if (u16State == 0xf000)
    {
        *out_pbDebouncedButtonWasPressed = TRUE;
    }
    *out_pbDebouncedButtonWasPressed = FALSE;
}

void Button_execute(void)
{
    BOOL bButtonWasPressed;
    Button_wasPressed(&bButtonWasPressed);
    if (bButtonWasPressed)
    {
        msg_t sMsg;
        sMsg.eMsgId = MSG_ID_0100;
        sMsg.u16DataSize = 0;
        sMsg.au8DataBytes = NULL;
        status_e tStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(tStatus != STATUS_SUCCESS), "MessageBroker_publish() failed with error code: %d", tStatus);
    }
}
