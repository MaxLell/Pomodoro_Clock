#include "PomodoroFsm.h"
#include "MessageBroker.h"

STATIC PomodoroFsm_state_e ePomodoroFsmState;

STATIC status_t PomodoroFsm_buttonPressedCallback(MessageBroker_message_t in_sMessage)
{
    return STATUS_OK;
}

void PomodoroFsm_init(void)
{
    // Set the initial state of the FSM to idle
    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    // Subscribe to the Button Event
    MessageBroker_subscribe(
        E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_buttonPressedCallback);

    // Subscribe to the LightControl State Messages

    // Subscribe to the current Minute
}

void PomodoroFsm_execute(void)
{
    switch (ePomodoroFsmState)
    {
    case E_PFSM_STATE_IDLE:
    {
        // Do nothing
        break;
    }
    case E_PFSM_STATE_WORKTIME:
    {
        // Do nothing
        break;
    }
    case E_PFSM_STATE_BREAKTIME:
    {
        // Do nothing
        break;
    }
    case E_PFSM_STATE_SEEKING_ATTENTION:
    {
        // Do nothing
        break;
    }
    default:
    {
        log_error("Invalid state: %d", ePomodoroFsmState);
        break;
    }
    }
}