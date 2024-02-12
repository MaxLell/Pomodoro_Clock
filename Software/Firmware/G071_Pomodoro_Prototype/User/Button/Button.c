#include "Button.h"
#include "Button_Hardware.h"
#include "Button_Datatypes.h"
#include "MessageDefinitions.h"

#include "MessageBroker.h"
#include "Common.h"

#define LONG_PRESS_PERIOD_MS 500
#define NUMBER_OF_BUTTONS 2
#define TRIGGER_BTN_IDX 0
#define ENCODER_BTN_IDX 1

Button_s sButtons[NUMBER_OF_BUTTONS] = {0};

BOOL bInitialized = FALSE;

/**
 * Taken from https://web.archive.org/web/20230223060958/http://www.ganssle.com/debouncing-pt2.htm
 */
void Button_getDebouncedState(Button_s *const inout_psButton)
{
    // Work with local copies due to better readability
    uint32_t u32State = inout_psButton->sDebounceFlags.u32State;
    u32State = (u32State << 1) | !Button_getState(inout_psButton->eButton) | 0x0;

    // // Print out the state in binary
    // log_info("Button State: %d%d %d%d %d%d %d%d", (u32State & 0x8000) >> 15, (u32State & 0x4000) >> 14,
    //          (u32State & 0x2000) >> 13, (u32State & 0x1000) >> 12, (u32State & 0x0800) >> 11, (u32State & 0x0400) >> 10, (u32State & 0x0200) >> 9, (u32State & 0x0100) >> 8);

    uint16_t u16LongPressState = inout_psButton->sDebounceFlags.u16LongPressState;
    BOOL bLongPressTriggered = inout_psButton->sDebounceFlags.bLongPressTriggered;
    if (u32State == 0x0000ffff)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = FALSE;
        u16LongPressState = 0;

        inout_psButton->eEvent = E_BTN_EVENT_SHORT_PRESSED;
    }

    if (u32State == 0xffff0000)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = FALSE;
        u16LongPressState = 0;

        inout_psButton->eEvent = E_BTN_EVENT_RELEASED;
    }

    if ((u32State == 0xffffffff) && (bLongPressTriggered == FALSE))
    {
        u16LongPressState++;
        if (u16LongPressState == LONG_PRESS_PERIOD_MS)
        {
            // Clear the current long button press progress so that it does not carry over to the next button press
            bLongPressTriggered = TRUE;
            u16LongPressState = 0;

            inout_psButton->eEvent = E_BTN_EVENT_LONG_PRESSED;
        }
    }
    // Update the parsed entries
    inout_psButton->sDebounceFlags.u32State = u32State;
    inout_psButton->sDebounceFlags.u16LongPressState = u16LongPressState;
    inout_psButton->sDebounceFlags.bLongPressTriggered = bLongPressTriggered;
}

void Button_TimIsr(void)
{
    if (bInitialized == FALSE)
    {
        return;
    }

    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        // Update the Debounced State of the Buttons
        Button_getDebouncedState(&sButtons[i]);
    }
}

void Button_execute(void)
{
    // Iterate over the buttons and publish Messages, when the State is different from Invalid
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        if (E_BTN_EVENT_INVALID != sButtons[i].eEvent)
        {
            // Prepare the Button Message
            ButtonMessage_s sMsgContent;
            sMsgContent.eButton = sButtons[i].eButton;
            sMsgContent.eEvent = sButtons[i].eEvent;

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_0103;
            sMsg.au8DataBytes = (uint8_t *)&sMsgContent;
            sMsg.u16DataSize = sizeof(ButtonMessage_s);

            // Publish the Button Message
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(STATUS_ERROR == eStatus), "Button_execute: Failed to publish Button Message");
            unused(eStatus); // Suppress the unused variable warning

            // Reset the Event to Invalid
            sButtons[i].eEvent = E_BTN_EVENT_INVALID;
        }
    }
}

void Button_init(void)
{
    // Initialize the Trigger Button
    sButtons[TRIGGER_BTN_IDX].eButton = E_BUTTON_TRIGGER;

    // Initialize the Encoder Button
    sButtons[ENCODER_BTN_IDX].eButton = E_BUTTON_ENCODER;

    bInitialized = TRUE;
}
