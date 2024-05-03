#include "ContextMgmtTask.h"
#include "Delay.h"
#include "Arduino.h"
#include "ContextManagement.h"
#include "Common.h"

static TaskHandle_t sTaskHandle = NULL;

void ContextMgmtTask(void *pvParameters)
{
    unused(pvParameters);
    ContextManagement_init();

    while (1)
    {
        ContextManagement_execute();
        Delay_ms(1);
    }

    ContextMgmtTask_deleteTask();
    ASSERT_MSG(false, "Should never reach here");
}

void ContextMgmtTask_createTask(void)
{
    BaseType_t xReturned = xTaskCreate(
        ContextMgmtTask,   // Pointer to the task entry function
        "ContextMgmtTask", // Descriptive name for the task
        2048,              // Stack size (bytes for an ESP32 target)
        NULL,              // Task input parameters
        1,                 // Task priority
        &sTaskHandle       // Task handle
    );

    ASSERT_MSG(xReturned == pdPASS, "Task creation failed");
}

void ContextMgmtTask_deleteTask(void)
{
    ASSERT_MSG(sTaskHandle != NULL, "Task handle is NULL");
    vTaskDelete(sTaskHandle);
}