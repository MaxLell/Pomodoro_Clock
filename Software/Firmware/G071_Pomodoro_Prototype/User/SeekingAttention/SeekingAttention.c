#include "SeekingAttention.h"

#include "Common.h"
#include "MessageBroker.h"

#include "CountdownTimer.h"

#include "LightEffects.h"

#include <stdlib.h>

/************************************************************
 * Private Defines
 ************************************************************/

#define SEEKING_ATTENTION_TEST

#ifndef SEEKING_ATTENTION_TEST
#define MAX_MS 20000
#define MIN_MS 10000
#else
#define MAX_MS 2000
#define MIN_MS 1000
#endif

/************************************************************
 * Private Data Types
 ************************************************************/
typedef struct
{
    BOOL bIsActive;
    BOOL bSeekingAttentionIsActive;
} SeekingAttention_internalState_s;

/************************************************************
 * Private Variables
 ************************************************************/
LightEffects_SeekingAttention_s sSeekingAttentionHandle = {0};

STATIC timer_t sSeekingAttentionTimer = {0};
STATIC timer_t sIncrementTimer = {0};
STATIC SeekingAttention_internalState_s sInternalState = {0};

/************************************************************
 * Implementation
 ************************************************************/

status_e SeekingAttention_MsgCallback(const msg_t *const in_sMsg)
{
    status_e eStatus = STATUS_SUCCESS;

    switch (in_sMsg->eMsgId)
    {
    case MSG_0900:
        sInternalState.bIsActive = TRUE;
        sSeekingAttentionTimer.u32StartTimeMs = 0;
        Countdown_startTimer(&sSeekingAttentionTimer);
        break;

    case MSG_0901:
    {
        ASSERT_MSG(!(TRUE != sInternalState.bIsActive), "Seeking Attention must be active first active");

        // Reset the flags
        sInternalState.bIsActive = FALSE;
        sInternalState.bSeekingAttentionIsActive = FALSE;

        // Clear the current Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Stop the Timer
        Countdown_stopTimer(&sSeekingAttentionTimer);

        // Publish the Finished Message - now Seeking Attention is basically reset and will no longer run
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0902;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(STATUS_SUCCESS != eStatus), "Message could not be published")
        unused(eStatus); // suppress warning when ASSERTS are not compiled
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
    status_e eStatus = MessageBroker_subscribe(MSG_0900, SeekingAttention_MsgCallback);
    ASSERT_MSG(!(STATUS_SUCCESS != eStatus), "Subscription failed")

    // Subscribe Seeking Attention Stop
    eStatus = MessageBroker_subscribe(MSG_0901, SeekingAttention_MsgCallback);
    ASSERT_MSG(!(STATUS_SUCCESS != eStatus), "Subscription failed")

    // Setup and start the timer
    uint32_t u32TimerPeriod;
    HelperFunction_getPseudoRandomNumber(MIN_MS, MAX_MS, &u32TimerPeriod);
    Countdown_initTimerMs(&sSeekingAttentionTimer, u32TimerPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sSeekingAttentionTimer);

    // Setup the Increment Timer
    Countdown_initTimerMs(&sIncrementTimer, 3, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_startTimer(&sIncrementTimer);
}

void SeekingAttention_execute(void)
{
    if (TRUE == sInternalState.bIsActive)
    {
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sSeekingAttentionTimer))
        {
            sInternalState.bSeekingAttentionIsActive = TRUE;

            // change the Timer Period by a random amount
            HelperFunction_getPseudoRandomNumber(MIN_MS, MAX_MS, &sSeekingAttentionTimer.u32TimerPeriod);

            // Reset the Increment Timer
            sIncrementTimer.u32StartTimeMs = 0;
        }
    }

    if (TRUE == sInternalState.bSeekingAttentionIsActive)
    {
        // Run the RenderSeekingAttention Function (but only if the Increment Timer has expired)
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sIncrementTimer))
        {
            LightEffects_RenderSeekingAttention(&sSeekingAttentionHandle);
        }

        // When the Sequence is properly rendered then reset the bSeekingAttentionIsActive flag
        if (TRUE == sSeekingAttentionHandle.bSequenceComplete)
        {
            sInternalState.bSeekingAttentionIsActive = FALSE;
        }
    }
}
