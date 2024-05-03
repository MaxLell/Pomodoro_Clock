#include "SeekingAttentionTask.h"
#include "SeekingAttention.h"
#include "Common.h"
#include "Delay.h"
#include "Arduino.h"

static TaskHandle_t sTaskHandle = NULL;

static void SeekingAttentionTask(void *pvParameters)
{
    (void)pvParameters;
    SeekingAttention_init();
    for (;;)
    {
        SeekingAttention_execute();
        Delay_ms(1);
    }
    SeekingAttentionTask_deleteTask();
    ASSERT_MSG(false, "Task just exited - should never happen");
}

void SeekingAttentionTask_createTask(void)
{
    BaseType_t xReturned = xTaskCreate(
        SeekingAttentionTask,   // Pointer to the task entry function
        "SeekingAttentionTask", // Descriptive name for the task
        2048,                   // Stack size (bytes for an ESP32 target)
        NULL,                   // Task input parameters
        1,                      // Task priority
        &sTaskHandle            // Task handle
    );

    ASSERT_MSG(xReturned == pdPASS, "Task creation failed");
}

void SeekingAttentionTask_deleteTask(void)
{
    ASSERT_MSG(sTaskHandle != NULL, "Task handle is NULL");
    vTaskDelete(sTaskHandle);
}