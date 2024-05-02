#include "PomodoroTask.h"
#include "Delay.h"
#include "PomodoroControl.h"
#include "Arduino.h"

static TaskHandle_t sTaskHandle = NULL;

static void Pomodoro_task(void *pvParameters)
{
    unused(pvParameters);

    // Init the Pomodoro
    PomodoroControl_init();

    for (;;)
    {
        // Run the Pomodoro Sequence
        PomodoroControl_execute();

        Delay_ms(1); // So that the scheduler can switch task
    }

    // Delete the task if it ever breaks out of the loop
    PomodoroTask_deleteTask();
    ASSERT_MSG(0, "Task just exited - should never happen");
}

void PomodoroTask_createTask(void)
{
    BaseType_t xReturned = xTaskCreate(
        Pomodoro_task,   // Pointer to the task entry function
        "Pomodoro_task", // Descriptive name for the task
        2048,            // Stack size (bytes for an ESP32 target)
        NULL,            // Task input parameters
        1,               // Task priority
        &sTaskHandle     // Task handle
    );

    ASSERT_MSG(xReturned == pdPASS, "Task creation failed");
}

void PomodoroTask_deleteTask(void)
{
    ASSERT_MSG(sTaskHandle != NULL, "Task handle is NULL");
    vTaskDelete(sTaskHandle);
}