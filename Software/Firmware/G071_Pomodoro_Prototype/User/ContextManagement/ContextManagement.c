#include "ContextManagement.h"

#include "Common.h"
#include "MessageBroker.h"
#include "MessageDefinitions.h"
#include "FSM.h"

/*********************************************
 * Private Data
 *********************************************/
STATIC BOOL bRunOnce = FALSE;
STATIC BOOL bSeekingAttentionIsFinished = FALSE;
STATIC ButtonMessage_s sButtonMessage = {0};

/*********************************************
 * State Definitions
 *********************************************/
typedef enum
{
    STATE_IDLE = 0U,
    STATE_POMODORO,
    STATE_SETTINGS,
    STATE_LAST
} ContextManagement_State_e;

/*********************************************
 * State Transition Events
 *********************************************/
typedef enum
{
    EVENT_BUTTON_TRIGGER_BTN_PRESSED = 0U,
    EVENT_ROTATY_ENCODER_BTN_PRESSED,
    EVENT_POMODORO_COMPLETE,
    EVENT_SETTING_COMPLETE,
    EVENT_LAST
} ContextManagement_Event_e;

/*********************************************
 * State Actions
 *********************************************/
STATIC void ContextManagement_IdleStateFunction(void);
STATIC void ContextManagement_PomodoroStateFunction(void);
STATIC void ContextManagement_SettingStateFunction(void);

STATIC const FSM_StateActionCb aStateActions[] = {
    [STATE_IDLE] = ContextManagement_IdleStateFunction,
    [STATE_POMODORO] = ContextManagement_PomodoroStateFunction,
    [STATE_SETTINGS] = ContextManagement_SettingStateFunction,
};

/*********************************************
 * State Transition Matrix
 *********************************************/
STATIC const uint16_t ContextManagement_transitionMatrix[STATE_LAST][EVENT_LAST] = {
    [STATE_IDLE] = {
        [EVENT_BUTTON_TRIGGER_BTN_PRESSED] = STATE_POMODORO,
        [EVENT_ROTATY_ENCODER_BTN_PRESSED] = STATE_SETTINGS,
        [EVENT_POMODORO_COMPLETE] = STATE_IDLE,
        [EVENT_SETTING_COMPLETE] = STATE_IDLE,
    },
    [STATE_POMODORO] = {
        [EVENT_BUTTON_TRIGGER_BTN_PRESSED] = STATE_POMODORO,
        [EVENT_ROTATY_ENCODER_BTN_PRESSED] = STATE_POMODORO,
        [EVENT_POMODORO_COMPLETE] = STATE_IDLE,
        [EVENT_SETTING_COMPLETE] = STATE_POMODORO,
    },
    [STATE_SETTINGS] = {
        [EVENT_BUTTON_TRIGGER_BTN_PRESSED] = STATE_SETTINGS,
        [EVENT_ROTATY_ENCODER_BTN_PRESSED] = STATE_SETTINGS,
        [EVENT_POMODORO_COMPLETE] = STATE_SETTINGS,
        [EVENT_SETTING_COMPLETE] = STATE_IDLE,
    },
};

/*********************************************
 * Generate the FSM Configuration
 *********************************************/
STATIC FSM_Config_t sContextManagementFsmConfig = {
    .NUMBER_OF_STATES = STATE_LAST,
    .NUMBER_OF_EVENTS = EVENT_LAST,
    .au16TransitionMatrix = (const uint16_t *)ContextManagement_transitionMatrix,
    .asStateActions = (const FSM_StateActionCb *)aStateActions,
    .u16CurrentState = STATE_IDLE,
    .u16CurrentEvent = EVENT_POMODORO_COMPLETE,
};

/*********************************************
 * State Functions Implementation
 *********************************************/

STATIC void ContextManagement_IdleStateFunction(void)
{
    status_e eStatus = STATUS_OK;

    if (bRunOnce == FALSE)
    {
        // Initialize the Idle State
        bRunOnce = TRUE;

        // Send out the Start Seeking Attention Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0900;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to publish MSG_0900");
    }

    // Only execute this section, when the Trigger Btn or the Rotary Encoder Btn is released
    if (((sButtonMessage.eButton == E_BUTTON_TRIGGER) && (sButtonMessage.eEvent == E_BTN_EVENT_SHORT_PRESSED)) ||
        ((sButtonMessage.eButton == E_BUTTON_ENCODER) && (sButtonMessage.eEvent == E_BTN_EVENT_LONG_PRESSED)))
    {
        // Send out the Stop Seeking Attention Message
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0901;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to publish MSG_0901");

        if (FALSE == bSeekingAttentionIsFinished)
        {
            return;
        }

        if (E_BUTTON_TRIGGER == sButtonMessage.eButton)
        {
            // reset the RunOnce Flag
            bRunOnce = FALSE;

            // Reset the BTN back to invalid
            sButtonMessage.eButton = E_BUTTON_INVALID;
            sButtonMessage.eEvent = E_BTN_EVENT_INVALID;

            // Reset the Seeking Attention Finished Flag
            bSeekingAttentionIsFinished = FALSE;

            // Send out the Start Pomodoro Message
            sMsg.eMsgId = MSG_0200;
            eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to publish MSG_0200");

            // Set the Trigger Event to EVENT_BUTTON_TRIGGER_BTN_PRESSED
            FSM_setTriggerEvent(&sContextManagementFsmConfig, EVENT_BUTTON_TRIGGER_BTN_PRESSED);
        }
        else if (E_BUTTON_ENCODER == sButtonMessage.eButton)
        {
            // reset the RunOnce Flag
            bRunOnce = FALSE;

            // Reset the BTN back to invalid
            sButtonMessage.eButton = E_BUTTON_INVALID;
            sButtonMessage.eEvent = E_BTN_EVENT_INVALID;

            // Reset the Seeking Attention Finished Flag
            bSeekingAttentionIsFinished = FALSE;

            // Send out the Start Setting Message
            sMsg.eMsgId = MSG_0700;
            eStatus = MessageBroker_publish(&sMsg);
            ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to publish MSG_0700");

            // Set the Trigger Event to EVENT_ROTATY_ENCODER_BTN_PRESSED
            FSM_setTriggerEvent(&sContextManagementFsmConfig, EVENT_ROTATY_ENCODER_BTN_PRESSED);
        }
        else
        {
            // This must never happen
            ASSERT_MSG(FALSE, "Invalid Button Type: %d, Event Type: %d", sButtonMessage.eButton, sButtonMessage.eEvent);
        }
    }
    unused(eStatus);
    return;
}

STATIC void ContextManagement_PomodoroStateFunction(void)
{
    // Do nothing - wait and listen for the Pomodoro Complete Message
    // This is triggered in the Message Callback
}

STATIC void ContextManagement_SettingStateFunction(void)
{
    // Do nothing - wait and listen for the Setting Complete Message
    // This is triggered in the Message Callback
}

/*********************************************
 * Module Functions Implementation
 *********************************************/

status_e ContextManagement_MsgCallback(const msg_t *const in_sMsg)
{
    status_e eStatus = STATUS_OK;

    switch (in_sMsg->eMsgId)
    {
    case MSG_0103:
    {
        // Parse the Button Event
        sButtonMessage = *(ButtonMessage_s *)in_sMsg->au8DataBytes;

        // Button must not be invalid
        ASSERT_MSG(!(sButtonMessage.eButton == E_BUTTON_INVALID), "Invalid Button Type: %d", sButtonMessage.eButton);

        // Button Event must not be invalid
        ASSERT_MSG(!(sButtonMessage.eEvent == E_BTN_EVENT_INVALID), "Invalid Button Event: %d", sButtonMessage.eEvent);
    }
    break;

    case MSG_0902:
    {
        log_info("Seeking Attention Finished");
        bSeekingAttentionIsFinished = TRUE;
    }
    break;

    case MSG_0204:
    {
        log_info("Pomodoro Complete");
        FSM_setTriggerEvent(&sContextManagementFsmConfig, EVENT_POMODORO_COMPLETE);
    }
    break;

    case MSG_0701:
    {
        log_info("Setting Complete");
        FSM_setTriggerEvent(&sContextManagementFsmConfig, EVENT_SETTING_COMPLETE);
    }
    break;

    default:
        ASSERT_MSG(0, "Unknown Message ID: %d", in_sMsg->eMsgId);
        eStatus = STATUS_ERROR;
        break;
    }

    return eStatus;
}

void ContextManagement_init(void)
{
    // subscribe to the Button Event Message
    status_e eStatus = STATUS_OK;
    eStatus = MessageBroker_subscribe(MSG_0103, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0103");

    // Subscribe to Seeking Attention finished Message
    eStatus = MessageBroker_subscribe(MSG_0902, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0901");

    // Subscribe to the Pomodoro Complete Message
    eStatus = MessageBroker_subscribe(MSG_0204, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0204");

    // Subscribe to the Setting Complete Message
    eStatus = MessageBroker_subscribe(MSG_0701, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_OK), "Failed to subscribe to MSG_0701");

    // Reset the RunOnce Flag
    bRunOnce = FALSE;

    // Reset the BTN back to invalid
    sButtonMessage.eButton = E_BUTTON_INVALID;
    sButtonMessage.eEvent = E_BTN_EVENT_INVALID;

    // Reset the Seekin Attention Finished Flag
    bSeekingAttentionIsFinished = FALSE;
}

void ContextManagement_execute(void)
{
    // Run the Statemachine
    FSM_execute(&sContextManagementFsmConfig);
}