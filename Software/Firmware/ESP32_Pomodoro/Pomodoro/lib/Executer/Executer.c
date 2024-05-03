#include "Executer.h"
#include "MessageBroker.h"
#include "RgbLed.h"
#include "InputSampling.h"
#include "PomodoroTask.h"
#include "ScoreTask.h"
#include "CfgStore.h"
#include "SeekingAttentionTask.h"
#include "ContextMgmtTask.h"

void Executer_init(void)
{
    // Utilities
    {
        // Initialize the Message Broker
        MessageBroker_init();

        // Initialize the RgbLed
        RgbLed_init();

        // Clear the RgbLeds
        RgbLed_clear();

        // Initialize the CfgStore
        CfgStore_init();
    }

    // Tasks
    {
        // Start the Input Sampling Task
        InputSampling_createTask();

        // Start the Pomodoro Task
        PomodoroTask_createTask();

        // Start the Score Task
        ScoreTask_createTask();

        // Start the Seeking Attention Task
        SeekingAttentionTask_createTask();

        // Start the Context Mgmt Task
        ContextMgmtTask_createTask();
    }
}

void Executer_execute(void)
{
    // Nothing much to be done here
}
