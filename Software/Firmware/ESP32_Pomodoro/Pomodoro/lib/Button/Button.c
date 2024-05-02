#include "Button.h"
#include "Button_Hardware.h"
#include "Button_Datatypes.h"
#include "MessageDefinitions.h"

#include "MessageBroker.h"
#include "Common.h"

#define LONG_PRESS_PERIOD_MS 500
#define NUMBER_OF_BUTTONS 1 // Only one button for now
#define TRIGGER_BTN_IDX 0

Button_s sButtons[NUMBER_OF_BUTTONS] = {0};

bool bInitialized = false;

/**
 * Taken from https://web.archive.org/web/20230223060958/http://www.ganssle.com/debouncing-pt2.htm
 */
void Button_getSampleAndDebouncedState(Button_s *const inout_psButton)
{
    // Work with local copies due to better readability
    u32 u32State = inout_psButton->sDebounceFlags.u32State;
    u32State = (u32State << 1) | !BtnHw_getState(inout_psButton->eButton) | 0x0;

    // // Print out the state in binary
    // log_info("Button State: %d%d %d%d %d%d %d%d", (u32State & 0x8000) >> 15, (u32State & 0x4000) >> 14,
    //          (u32State & 0x2000) >> 13, (u32State & 0x1000) >> 12, (u32State & 0x0800) >> 11, (u32State & 0x0400) >> 10, (u32State & 0x0200) >> 9, (u32State & 0x0100) >> 8);

    u16 u16LongPressState = inout_psButton->sDebounceFlags.u16LongPressState;
    bool bLongPressTriggered = inout_psButton->sDebounceFlags.bLongPressTriggered;
    if (u32State == 0x0000ffff)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = false;
        u16LongPressState = 0;

        inout_psButton->eEvent = E_BTN_EVENT_SHORT_PRESSED;
    }

    if (u32State == 0xffff0000)
    {
        // Clear the current long button press progress so that it does not carry over to the next button press
        bLongPressTriggered = false;
        u16LongPressState = 0;

        inout_psButton->eEvent = E_BTN_EVENT_RELEASED;
    }

    if ((u32State == 0xffffffff) && (bLongPressTriggered == false))
    {
        u16LongPressState++;
        if (u16LongPressState == LONG_PRESS_PERIOD_MS)
        {
            // Clear the current long button press progress so that it does not carry over to the next button press
            bLongPressTriggered = true;
            u16LongPressState = 0;

            inout_psButton->eEvent = E_BTN_EVENT_LONG_PRESSED;
        }
    }
    // Update the parsed entries
    inout_psButton->sDebounceFlags.u32State = u32State;
    inout_psButton->sDebounceFlags.u16LongPressState = u16LongPressState;
    inout_psButton->sDebounceFlags.bLongPressTriggered = bLongPressTriggered;
}

void Button_execute(void)
{
    ASSERT_MSG(bInitialized, "Button_execute: Not initialized");

    /**
     * Sample and debounce the buttons
     */
    for (u8 i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        // Update the Debounced State of the Buttons
        Button_getSampleAndDebouncedState(&sButtons[i]);
    }

    /**
     * Publish the Button Messages
     */
    for (u8 i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        if (E_BTN_EVENT_INVALID != sButtons[i].eEvent)
        {
            // Prepare the Button Message
            ButtonMessage_s sMsgContent;
            sMsgContent.eButton = sButtons[i].eButton;
            sMsgContent.eEvent = sButtons[i].eEvent;

            msg_t sMsg = {0};
            sMsg.eMsgId = MSG_0103;
            sMsg.au8DataBytes = (u8 *)&sMsgContent;
            sMsg.u16DataSize = sizeof(ButtonMessage_s);

            // Publish the Button Message
            status_e eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(STATUS_ERROR == eStatus), "Button_execute: Failed to publish Button Message");
            unused(eStatus); // Suppress the unused variable warning

            // Reset the Event to Invalid
            sButtons[i]
                .eEvent = E_BTN_EVENT_INVALID;
        }
    }
}

void Button_init(void)
{
    // Initialize the Trigger Button
    sButtons[TRIGGER_BTN_IDX].eButton = E_BTN_TRIGGER;

    // Initialize the Hardware
    BtnHw_init();

    bInitialized = true;
}
