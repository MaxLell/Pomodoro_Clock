#include "Button.h"
#include "Button_Hardware.h"

#include "MessageBroker.h"

#define LONG_PRESS_PERIOD_MS 500

typedef struct
{
    BOOL bButtonWasShortPressed;
    BOOL bButtonWasReleased;
    BOOL bButtonWasLongPressed;
} ButtonState_s;

STATIC ButtonState_s sButtonState = {FALSE, FALSE, FALSE};

/**
 * Taken from https://web.archive.org/web/20230223060958/http://www.ganssle.com/debouncing-pt2.htm
 */
void Button_getDebouncedState(ButtonState_s *inout_psButtonState)
{
    static uint32_t u32State = 0;
    u32State = (u32State << 1) | !Button_getState() | 0x0;

    // Print out the state in binary
    // log_info("Button State: %d%d %d%d %d%d %d%d", (u32State & 0x8000) >> 15, (u32State & 0x4000) >> 14,
    //          (u32State & 0x2000) >> 13, (u32State & 0x1000) >> 12, (u32State & 0x0800) >> 11, (u32State & 0x0400) >>
    //          10, (u32State & 0x0200) >> 9, (u32State & 0x0100) >> 8);

    static uint16_t u16LongPressState = 0;
    static BOOL bLongPressTriggered = FALSE;
    if (u32State == 0x0000ffff)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = FALSE;
        u16LongPressState = 0;

        inout_psButtonState->bButtonWasShortPressed = TRUE;
    }

    if (u32State == 0xffff0000)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = FALSE;
        u16LongPressState = 0;

        inout_psButtonState->bButtonWasReleased = TRUE;
    }

    if ((u32State == 0xffffffff) && (bLongPressTriggered == FALSE))
    {
        u16LongPressState++;
        if (u16LongPressState == LONG_PRESS_PERIOD_MS)
        {
            // Clear the current long button press progress so that it does not carry over to the next button press
            bLongPressTriggered = TRUE;
            u16LongPressState = 0;

            inout_psButtonState->bButtonWasLongPressed = TRUE;
        }
    }
}

void Button_TimIsr(void)
{
    Button_getDebouncedState(&sButtonState);
}

void Button_execute(void)
{
    if (sButtonState.bButtonWasShortPressed == TRUE)
    {
        // Publish Button Short pressed Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0100;
        status_e tStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(tStatus != STATUS_SUCCESS), "MessageBroker_publish() failed with error code: %d", tStatus);

        // Clear the Button State when it is used
        sButtonState.bButtonWasShortPressed = FALSE;
    }

    if (sButtonState.bButtonWasLongPressed == TRUE)
    {
        // Clear the Button State when it is used
        sButtonState.bButtonWasLongPressed = FALSE;

        // Publish Button Long pressed Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0101;
        status_e tStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(tStatus != STATUS_SUCCESS), "MessageBroker_publish() failed with error code: %d", tStatus);
    }

    if (sButtonState.bButtonWasReleased == TRUE)
    {
        // Clear the Button State when it is used
        sButtonState.bButtonWasReleased = FALSE;

        // Publish Button Released Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_ID_0102;
        status_e tStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(tStatus != STATUS_SUCCESS), "MessageBroker_publish() failed with error code: %d", tStatus);
    }
}
