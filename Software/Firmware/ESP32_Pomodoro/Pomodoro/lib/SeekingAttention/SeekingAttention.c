#include "SeekingAttention.h"

#include "Common.h"
#include "MessageBroker.h"

#include "CountdownTimer.h"

#include "LightEffects.h"

#include <stdlib.h>

/************************************************************
 * Private Defines
 ************************************************************/

#define MAX_MS 20000
#define MIN_MS 10000

/************************************************************
 * Private Data Types
 ************************************************************/
typedef struct
{
    bool bIsActive;
    bool bSeekingAttentionIsActive;
    u32 u32MaxTimeMs;
    u32 u32MinTimeMs;
} SeekingAttention_internalState_s;

/************************************************************
 * Private Variables
 ************************************************************/
STATIC LightEffects_SeekingAttention_s sSeekingAttentionHandle = {0};

STATIC CountdownTimer_t sSeekingAttentionTimer = {0};
STATIC CountdownTimer_t sIncrementTimer = {0};
STATIC SeekingAttention_internalState_s sInternalState = {0};

/************************************************************
 * Implementation
 ************************************************************/

status_e SeekingAttention_MsgCallback(const msg_t *const in_sMsg)
{
    status_e eStatus = STATUS_OK;

    switch (in_sMsg->eMsgId)
    {
    case MSG_0900:
        sInternalState.bIsActive = true;
        sSeekingAttentionTimer.u32StartTimeMs = 0;
        Countdown_resetAndStartTimer(&sSeekingAttentionTimer);
        break;

    case MSG_0901:
    {
        ASSERT_MSG(!(true != sInternalState.bIsActive), "Seeking Attention must be active first active");

        // Reset the flags
        sInternalState.bIsActive = false;
        sInternalState.bSeekingAttentionIsActive = false;

        // Clear the current Progress Rings
        LightEffects_ClearPomodoroProgressRings();

        // Stop the Timer
        Countdown_stopTimer(&sSeekingAttentionTimer);

        // Publish the Finished Message - now Seeking Attention is basically reset and will no longer run
        msg_t sMsg = {0};
        sMsg.eMsgId = MSG_0902;
        eStatus = MessageBroker_publish(&sMsg);
        ASSERT_MSG(!(STATUS_OK != eStatus), "Message could not be published")
        unused(eStatus); // suppress warning when ASSERTS are not compiled
    }
    break;

    case MSG_0005:
    {
        // Update the Min and Max Time
        sInternalState.u32MaxTimeMs = 1000;
        sInternalState.u32MinTimeMs = 500;

        // Stop the Timer
        Countdown_stopTimer(&sSeekingAttentionTimer);

        // Start the Timer with the new Min and Max Time
        u32 u32TimerPeriod;
        HelperFunction_getPseudoRandomNumber(sInternalState.u32MinTimeMs, sInternalState.u32MaxTimeMs, &u32TimerPeriod);
        Countdown_initTimerMs(&sSeekingAttentionTimer, u32TimerPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
        Countdown_resetAndStartTimer(&sSeekingAttentionTimer);
    }
    break;

    default:
        ASSERT_MSG(false, "wrong message");
    }

    return eStatus;
}

void SeekingAttention_init(void)
{
    // Subscribe Seeking Attention Start
    status_e eStatus = MessageBroker_subscribe(MSG_0900, SeekingAttention_MsgCallback);
    ASSERT_MSG(!(STATUS_OK != eStatus), "Subscription failed")

    // Subscribe Seeking Attention Stop
    eStatus = MessageBroker_subscribe(MSG_0901, SeekingAttention_MsgCallback);
    ASSERT_MSG(!(STATUS_OK != eStatus), "Subscription failed")

    // Subscribe to the Test Message
    eStatus = MessageBroker_subscribe(MSG_0005, SeekingAttention_MsgCallback);
    ASSERT_MSG(!(STATUS_OK != eStatus), "Subscription failed")

    // Initialize the internal state
    sInternalState.bIsActive = false;
    sInternalState.bSeekingAttentionIsActive = false;
    sInternalState.u32MaxTimeMs = MAX_MS;
    sInternalState.u32MinTimeMs = MIN_MS;

    // Setup and start the timer
    u32 u32TimerPeriod;
    HelperFunction_getPseudoRandomNumber(sInternalState.u32MinTimeMs, sInternalState.u32MaxTimeMs, &u32TimerPeriod);
    Countdown_initTimerMs(&sSeekingAttentionTimer, u32TimerPeriod, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&sSeekingAttentionTimer);

    // Setup the Increment Timer
    Countdown_initTimerMs(&sIncrementTimer, 3, E_OPERATIONAL_MODE_CONTIUNOUS);
    Countdown_resetAndStartTimer(&sIncrementTimer);
}

void SeekingAttention_execute(void)
{
    if (true == sInternalState.bIsActive)
    {
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sSeekingAttentionTimer))
        {
            sInternalState.bSeekingAttentionIsActive = true;

            // change the Timer Period by a random amount
            HelperFunction_getPseudoRandomNumber(sInternalState.u32MinTimeMs, sInternalState.u32MaxTimeMs, &sSeekingAttentionTimer.u32TimerPeriod);

            // Reset the Increment Timer
            sIncrementTimer.u32StartTimeMs = 0;
        }
    }

    if (true == sInternalState.bSeekingAttentionIsActive)
    {
        // Run the RenderSeekingAttention Function (but only if the Increment Timer has expired)
        if (E_COUNTDOWN_TIMER_EXPIRED == Countdown_getTimerStatus(&sIncrementTimer))
        {
            LightEffects_RenderSeekingAttention(&sSeekingAttentionHandle);
        }

        // When the Sequence is properly rendered then reset the bSeekingAttentionIsActive flag
        if (true == sSeekingAttentionHandle.bSequenceComplete)
        {
            sInternalState.bSeekingAttentionIsActive = false;
        }
    }
}
