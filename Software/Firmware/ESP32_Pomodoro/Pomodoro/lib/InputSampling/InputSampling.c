#include "InputSampling.h"
#include "Arduino.h"
#include "Common.h"
#include "Button.h"
#include "Delay.h"

static TaskHandle_t tTaskHandle = NULL;

static void InputSampling_task(void *pvParameters)
{
    unused(pvParameters);

    Button_init();

    for (;;)
    {
        Button_execute();

        // The sampling shall happen every 1ms
        Delay_ms(1);
    }

    // Delete the task if it ever breaks out of the loop
    InputSampling_taskDelete();
    ASSERT_MSG(0, "Task just exited - should never happen");
}

void InputSampling_taskCreate(void)
{
    BaseType_t xReturned = xTaskCreate(
        InputSampling_task,   // Pointer to the task entry function
        "InputSampling_task", // Descriptive name for the task
        2048,                 // Stack size (bytes for an ESP32 target)
        NULL,                 // Task input parameters
        1,                    // Task priority
        &tTaskHandle          // Task handle
    );

    ASSERT_MSG(xReturned == pdPASS, "Task creation failed");
}

void InputSampling_taskDelete(void)
{
    ASSERT_MSG(tTaskHandle != NULL, "Task handle is NULL");
    vTaskDelete(tTaskHandle);
}