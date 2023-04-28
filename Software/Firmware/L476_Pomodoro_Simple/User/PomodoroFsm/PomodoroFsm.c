#include "PomodoroFsm.h"
#include "MessageBroker.h"
#include "Config.h"
#include "Common.h"

/**
 * global static variables
 */
STATIC PomodoroFsm_state_e ePomodoroFsmState;
STATIC PomodoroFsm_inputs_t sPomodoroFsmInputs = {0};
STATIC MessageBroker_message_t sPublishingMessage = {0};
STATIC BOOL bRunOnce = FALSE;

/**
 * private functions
 */
STATIC void PomodoroFsm_calculateTimeStampsForChangingStates(
    uint8_t *inout_u8WorktimeEndMinute,
    uint8_t *inout_u8BreaktimeEndMinute,
    uint8_t *in_u8CurrentMinute);

STATIC status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage);

STATIC status_t PomodoroFsm_publishMessage(
    PomodoroFsm_state_e in_eNextState,
    PomodoroFsm_state_e in_eCurrentState);

STATIC void PomodoroFsm_calculateTimeStampsForChangingStates(
    uint8_t *inout_u8WorktimeEndMinute,
    uint8_t *inout_u8BreaktimeEndMinute,
    uint8_t *in_u8CurrentMinute)
{
    // Input Checks
    assert_true(inout_u8WorktimeEndMinute != NULL);
    assert_true(inout_u8BreaktimeEndMinute != NULL);
    assert_true(in_u8CurrentMinute != NULL);
    assert_true(*in_u8CurrentMinute < MINUTES_IN_HOUR);

    // Calculate the Time Stamps for the End of the Work Time and the Break Time
    uint8_t u8WorktimeIntervalMin = 0U;
    uint8_t u8BreaktimeIntervalMin = 0U;
    status_t sStatus;
    sStatus = Config_getWorktime(&u8WorktimeIntervalMin);
    sStatus = Config_getBreaktime(&u8BreaktimeIntervalMin);

    assert_true(sStatus == STATUS_OK);

    uint8_t u8CurrentMinute = *in_u8CurrentMinute;
    uint8_t u8WorktimeEndMin = (u8CurrentMinute + u8WorktimeIntervalMin) % MINUTES_IN_HOUR;
    uint8_t u8BreaktimeEndMin = (u8WorktimeEndMin + u8BreaktimeIntervalMin) % MINUTES_IN_HOUR;

    *inout_u8WorktimeEndMinute = u8WorktimeEndMin;
    *inout_u8BreaktimeEndMinute = u8BreaktimeEndMin;
}

STATIC status_t PomodoroFsm_callback(MessageBroker_message_t in_sMessage)
{
    switch (in_sMessage.eMsgTopic)
    {
    case E_TOPIC_TRIGGER_BUTTON_PRESSED:
    {
        sPomodoroFsmInputs.bButtonPressed = TRUE;
        break;
    }
    case E_TOPIC_TIME_AND_DATE:
    {
        // Get the current Minute
        sPomodoroFsmInputs.u8CurrentMinute = in_sMessage.au8DataBytes[1];

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
        E_TOPIC_TRIGGER_BUTTON_PRESSED,
        PomodoroFsm_callback);

    // Subscribe to the current Minute
    MessageBroker_subscribe(
        E_TOPIC_TIME_AND_DATE,
        PomodoroFsm_callback);
}

STATIC status_t PomodoroFsm_publishMessage(
    PomodoroFsm_state_e in_eNextState,
    PomodoroFsm_state_e in_eCurrentState)
{
    sPublishingMessage.eMsgTopic = E_TOPIC_PFSM_STATE_CHANGED;
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
        else if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            u8CurrentMinute = 0;
            u8PreviousMinute = 100;
            u8MinutesElapsedCounter = 0U;
            sPomodoroFsmInputs.bButtonPressed = FALSE;
            bRunOnce = TRUE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_WORKTIME,
                E_PFSM_STATE_IDLE);

            // Set the state to work time
            ePomodoroFsmState = E_PFSM_STATE_WORKTIME;
        }
        else
        {
            // Do nothing
        }
        break;
    }
    case E_PFSM_STATE_WORKTIME:
    {
        if (bRunOnce == FALSE)
        {
            bRunOnce = TRUE;

            // Calculate the timestamps for changing the state
            PomodoroFsm_calculateTimeStampsForChangingStates(
                &sPomodoroFsmInputs.u8WorktimeEndMin,
                &sPomodoroFsmInputs.u8BreaktimeEndMin,
                &sPomodoroFsmInputs.u8CurrentMinute);
        }

        /**
         * State Changes
         */

        // Change the state -> Idle (Button Pressed)
        if (sPomodoroFsmInputs.bButtonPressed)
        {
            // Reset respective variables
            sPomodoroFsmInputs.bButtonPressed = FALSE;
            bRunOnce = FALSE;

            // Set the state to break time
            ePomodoroFsmState = E_PFSM_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_IDLE,
                E_PFSM_STATE_WORKTIME);
        }

        // Change the state -> Breaktime (Time Elapsed)
        else if (sPomodoroFsmInputs.u8WorktimeEndMin == sPomodoroFsmInputs.u8CurrentMinute)
        {
            // Set the state to break time
            ePomodoroFsmState = E_PFSM_STATE_BREAKTIME;

            // Reset the RunOnce Flag
            bRunOnce = FALSE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_BREAKTIME,
                E_PFSM_STATE_WORKTIME);
        }
        else
        {
            // Do nothing
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

        else if (sPomodoroFsmInputs.u8BreaktimeEndMin == sPomodoroFsmInputs.u8CurrentMinute)
        {
            // Set the state to work time
            ePomodoroFsmState = E_PFSM_STATE_IDLE;

            // Publish the state change message
            PomodoroFsm_publishMessage(
                E_PFSM_STATE_IDLE,       // Next State
                E_PFSM_STATE_BREAKTIME); // Current State
        }
        else
        {
            // Do nothing
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