#include "Common.h"
#include "ScoreTask.h"
#include "Arduino.h"
#include "Score.h"
#include "Delay.h"

static TaskHandle_t sTaskHandle;

static void ScoreTask_taskFunction(void *pvParameters)
{
    unused(pvParameters);
    Score_init();

    for (;;)
    {
        Score_execute();
        Delay_ms(1);
    }

    // Delete the task if it ever breaks out of the loop
    ScoreTask_taskDelete();
    ASSERT_MSG(0, "Task just exited - should never happen");
}

void ScoreTask_createTask(void)
{
    BaseType_t xReturned = xTaskCreate(
        ScoreTask_taskFunction,   // Pointer to the task entry function
        "ScoreTask_taskFunction", // Descriptive name for the task
        2048,                     // Stack size (bytes for an ESP32 target)
        NULL,                     // Task input parameters
        1,                        // Task priority
        &sTaskHandle              // Task handle
    );

    ASSERT_MSG(xReturned == pdPASS, "Task creation failed");
}

void ScoreTask_taskDelete(void)
{
    vTaskDelete(sTaskHandle);
}