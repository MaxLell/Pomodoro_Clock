#include "Buzzer.h"
#include "Common.h"
#include "MessageBroker.h"
#include "MessageTopics.h"
#include "PomodoroFsm_Interface.h"
#include "Buzzer_Hardware.h"

#define BUZZER_RING_DURATION_SEC 5U
STATIC BOOL bRingBuzzer = FALSE;
STATIC uint8_t u8SecondsCounter = 0U;

status_t Buzzer_callback(MessageBroker_message_t in_sMessage)
{
    status_t sStatus = STATUS_OK;

    switch (in_sMessage.eMsgTopic)
    {
    case E_TOPIC_PFSM_STATE_CHANGED:
    {
        if ((in_sMessage.au8DataBytes[PFSM_NEW_STATE] == E_PFSM_STATE_IDLE) &&
            (in_sMessage.au8DataBytes[PFSM_OLD_STATE] == E_PFSM_STATE_BREAKTIME))
        {
            bRingBuzzer = TRUE;
            break;
        }

        return sStatus;
    }
    case E_TOPIC_ONE_SECOND_PASSED:
        if (bRingBuzzer)
        {
            u8SecondsCounter++;
        }
        break;

    default:
        log_error("Unknown Topic");
        sStatus = STATUS_INVALID_ARG;
        break;
    }
    return sStatus;
}

void Buzzer_Init(void)
{
    // Subscribe to the PFSM State Change Topic
    MessageBroker_subscribe(E_TOPIC_PFSM_STATE_CHANGED, Buzzer_callback);

    // Subscribe to the Second Passed Topic
    MessageBroker_subscribe(E_TOPIC_ONE_SECOND_PASSED, Buzzer_callback);
}

void Buzzer_execute(void)
{
    if (bRingBuzzer)
    {
        if (u8SecondsCounter < BUZZER_RING_DURATION_SEC)
        {
            u8SecondsCounter++;
            // Enable the Buzzer // TODO
        }
        if (u8SecondsCounter == BUZZER_RING_DURATION_SEC)
        {
            // Disable the Buzzer // TODO
            bRingBuzzer = FALSE;
            u8SecondsCounter = 0U;
        }
    }
}
