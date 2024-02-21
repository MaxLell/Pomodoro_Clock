#include "ContextManagement.h"

#include "Common.h"
#include "MessageBroker.h"

/*********************************************
 * State Definitions
 *********************************************/
typedef enum
{
    STATE_IDLE_SEEKING_ATTENTION = 0U,
    STATE_POMODORO_RUNNING,
    STATE_SETTING_RUNNING,
    STATE_LAST
} ContextManagement_State_e;

/*********************************************
 * State Transition Events
 *********************************************/
typedef enum
{
    EVENT_BUTTON_TRIGGER_BTN_PRESSED = 0U,
    EVENT_BUTTON_SHOULDER_BTN_1_LONG_PRESSED,
    EVENT_BUTTON_SHOULDER_BTN_2_LONG_PRESSED,
    EVENT_POMODORO_COMPLETE,
    EVENT_SETTING_COMPLETE,
    EVENT_LAST
} ContextManagement_Event_e;

/*********************************************
 * State Actions
 *********************************************/

/*********************************************
 * Generate the FSM Configuration
 *********************************************/

status_e ContextManagement_MsgCallback(const msg_t *const in_sMsg)
{
    status_e eStatus = STATUS_SUCCESS;

    switch (in_sMsg->eMsgId)
    {
    case MSG_0103:
    {
        // Button Event
    }
    break;

    case MSG_0003:
    {
        // Test Message
    }
    break;

    case MSG_0204:
    {
        // Pomodoro Complete
    }

    case MSG_0701:
    {
        // Setting Complete
    }

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
    status_e eStatus = STATUS_SUCCESS;
    eStatus = MessageBroker_subscribe(MSG_0103, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Failed to subscribe to MSG_0103");

    // subscribe to the Test Message
    eStatus = MessageBroker_subscribe(MSG_0003, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Failed to subscribe to MSG_0003");

    // Subscribe to the Pomodoro Complete Message
    eStatus = MessageBroker_subscribe(MSG_0204, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Failed to subscribe to MSG_0204");

    // Subscribe to the Setting Complete Message
    eStatus = MessageBroker_subscribe(MSG_0701, ContextManagement_MsgCallback);
    ASSERT_MSG(!(eStatus != STATUS_SUCCESS), "Failed to subscribe to MSG_0701");
}

void ContextManagement_execute(void)
{
    // Run the Statemachine
}