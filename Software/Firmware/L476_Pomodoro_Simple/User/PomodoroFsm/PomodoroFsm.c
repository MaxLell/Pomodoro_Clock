#include "PomodoroFsm.h"
#include "MessageBroker.h"
#include "LightControl.h"

STATIC PomodoroFsm_state_e ePomodoroFsmState;
STATIC PomodoroFsm_inputs_t sPomodoroFsmInputs = {0};
STATIC MessageBroker_message_t sPublishingMessage = {0};

STATIC status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage)
{
    switch (in_sMessage.eMsgTopic)
    {
    case E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED:
    {
        sPomodoroFsmInputs.bButtonPressed = TRUE;
        break;
    }
    case E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE:
    {
        // parse the current Minute from the data bytes
        // the data bytes are in the format: [Hour, Minute, Second, Day, Month, Year]
        // so the minute is the second byte -> Index 1
        sPomodoroFsmInputs.u8CurrentMinute = in_sMessage.au8DataBytes[1];
        break;
    }
    case E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED:
    {
        sPomodoroFsmInputs.u8LightControlState = in_sMessage.au8DataBytes[0];
        break;
    }
    default:
    {
        log_error("Invalid topic: %d", in_sMessage.eTopic);
        return STATUS_INVALID_ARG;
        break;
    }
    }
    return STATUS_OK;
}

void PomodoroFsm_init(void)
{
    // Set the initial state of the FSM to idle
    ePomodoroFsmState = E_PFSM_STATE_IDLE;

    // Subscribe to the Button Event
    MessageBroker_subscribe(
        E_MESSAGE_BROKER_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_callback);

    // Subscribe to the current Minute
    MessageBroker_subscribe(
        E_MESSAGE_BROKER_TOPIC_TIME_AND_DATE,
        PomodoroFsm_callback);

    // Subscribe to the LightControl State Messages
    MessageBroker_subscribe(
        E_MESSAGE_BROKER_TOPIC_LCTRL_STATE_CHANGED,
        PomodoroFsm_callback);
}

STATIC status_t PomodoroFsm_publishMessage(
    PomodoroFsm_state_e in_eNextState,
    PomodoroFsm_state_e in_eCurrentState)
{
    sPublishingMessage.eMsgTopic = E_MESSAGE_BROKER_TOPIC_PFSM_STATE_CHANGED;
    sPublishingMessage.u16DataSize = 2;
    uint8_t au8Data[2] = {in_eNextState, in_eCurrentState};
    sPublishingMessage.au8DataBytes = au8Data;
    status_t eStatus = MessageBroker_publish(sPublishingMessage);
    return eStatus;
}

void PomodoroFsm_execute(void)
{
    switch (ePomodoroFsmState)
    {
    case E_PFSM_STATE_IDLE:
    {
        uint8_t u8CurrentMinute = 0;
        uint8_t u8PreviousMinute = 100;
        static uint8_t u8MinutesElapsedCounter = 0U;

        // if the minute changes then increment the minutesElapsedCounter
        u8CurrentMinute = sPomodoroFsmInputs.u8CurrentMinute;
        if (u8CurrentMinute != u8PreviousMinute)
        {
            u8MinutesElapsedCounter++;
            u8PreviousMinute = u8CurrentMinute;
        }
        // State Changes
        // State change to 'seeking attention' after 5 minutes
        if (u8MinutesElapsedCounter > 5U)
        {
            // Reset respective variables
            u8CurrentMinute = 0;
            u8PreviousMinute = 100;
            u8MinutesElapsedCounter = 0U;
            sPomodoroFsmInputs.bButtonPressed = FALSE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_SEEKING_ATTENTION,
                E_PFSM_STATE_IDLE);

            ePomodoroFsmState = E_PFSM_STATE_SEEKING_ATTENTION;
        }

        // State change to work time
        if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            u8CurrentMinute = 0;
            u8PreviousMinute = 100;
            u8MinutesElapsedCounter = 0U;
            sPomodoroFsmInputs.bButtonPressed = FALSE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_WORKTIME,
                E_PFSM_STATE_IDLE);

            // Set the state to work time
            ePomodoroFsmState = E_PFSM_STATE_WORKTIME;
        }
        break;
    }
    case E_PFSM_STATE_WORKTIME:
    {
        if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            sPomodoroFsmInputs.bButtonPressed = FALSE;

            // Set the state to break time
            ePomodoroFsmState = E_PFSM_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_IDLE,
                E_PFSM_STATE_WORKTIME);
        }

        if (sPomodoroFsmInputs.u8LightControlState == E_LCTRL_STATE_POMODORO_BREAKTIME)
        {
            // Set the state to break time
            ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

            // reset the perceived light control state
            sPomodoroFsmInputs.u8LightControlState = E_LCTRL_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_BREAKTIME,
                E_PFSM_STATE_WORKTIME);
        }

        break;
    }
    case E_PFSM_STATE_BREAKTIME:
    {
        if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            sPomodoroFsmInputs.bButtonPressed = FALSE;

            // Set the state to idle
            ePomodoroFsmState = E_PFSM_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_IDLE,
                E_PFSM_STATE_BREAKTIME);
        }

        if (sPomodoroFsmInputs.u8LightControlState == E_LCTRL_STATE_IDLE)
        {
            // Set the state to work time
            ePomodoroFsmState = E_PFSM_STATE_IDLE;

            // reset the perceived light control state
            sPomodoroFsmInputs.u8LightControlState = E_LCTRL_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_IDLE,       // Next State
                E_PFSM_STATE_BREAKTIME); // Current State
        }

        break;
    }
    case E_PFSM_STATE_SEEKING_ATTENTION:
    {
        if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            sPomodoroFsmInputs.bButtonPressed = FALSE;

            // Set the state to Wort Time
            ePomodoroFsmState = E_PFSM_STATE_WORKTIME;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_WORKTIME,
                E_PFSM_STATE_SEEKING_ATTENTION);
        }
        break;
    }
    default:
    {
        log_error("Invalid state: %d", ePomodoroFsmState);
        break;
    }
    }
}