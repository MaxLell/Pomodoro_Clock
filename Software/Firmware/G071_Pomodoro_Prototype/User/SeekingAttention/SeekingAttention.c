#include "SeekingAttention.h"

#include "Common.h"
#include "MessageBroker.h"

#include "CountdownTimer.h"

#include "LightEffects.h"

#include <stdlib.h>

#define MAX_MS 20000
#define MIN_MS 10000

/**
 * This function does only provide a Pseudo Random Number.
 * It is not super secure.
 */
uint32_t getPseudoRandomNumber(uint32_t min, uint32_t max)
{
    ASSERT_MSG(!(max <= min), "values need to be different");

    return ((uint32_t)rand() % (max - min + 1)) + min;
}

typedef struct
{
    BOOL bIsActive;
    BOOL bSeekingAttentionIsActive;
} SeekingAttention_internalState_s;

STATIC timer_t sSeekingAttentionTimer = {0};
STATIC SeekingAttention_internalState_s sInternalState = {0};

status_e SeekingAttention_MsgCallback(const msg_t *const in_sMsg)
{
    status_e eStatus = STATUS_SUCCESS;

    switch (in_sMsg->eMsgId)
    {
    case MSG_0900:
        sInternalState.bIsActive = TRUE;
        break;

    case MSG_0901:
    {
        // Reset the flags
        sInternalState.bIsActive = FALSE;
        sInternalState.bIsActive = FALSE;

        // Clear the current Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Publish the Finished Message - now Seeking Attention is basically reset and will no longer run
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0902;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(STATUS_SUCCESS != eStatus), "Message could not be published")
        unused(eStatus); // suppress warning
    }
    break;

    default:
        ASSERT_MSG(FALSE, "wrong message");
    }

    return eStatus;
}

void SeekingAttention_init(void)
{
    // Subscribe Seeking Attention Start

    // Subscribe Seeking Attention Stop

    // Setup and start the timer
    uint32_t u32TimerPeriod = getPseudoRandomNumber(MIN_MS, MAX_MS);
    Countdown_initTimerMs(&sSeekingAttentionTimer, u32TimerPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sSeekingAttentionTimer);
}

void SeekingAttention_execute(void)
{
    if (TRUE == sInternalState.bIsActive)
    {
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sSeekingAttentionTimer))
        {
            sInternalState.bSeekingAttentionIsActive = TRUE;

            // change the Timer Period by a random amount
            sSeekingAttentionTimer.u32TimerPeriod = getPseudoRandomNumber(MIN_MS, MAX_MS);
        }
    }

    if (TRUE == sInternalState.bSeekingAttentionIsActive)
    {
        // Run the Seeking Attention Sequence in LightControl

        // for the current time being this is only a log_info Statement.

        // When the Sequence is properly rendered then reset the bSeekingAttentionIsActive flag
    }
}
