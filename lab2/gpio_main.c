#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "include/button.h"

#define BUTTON_PIN GPIO_NUM_4
#define BUTTON_IDX 0

static void printStudentID(void *arg)
{
    int myID = 2010524;
    while (1)
    {
        printf("Student ID: %d\n", myID);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
// Function to be executed by the acyclic task
void buttonRead(void *pvParameters)
{
    static TickType_t xNextWakeTime;
    static uint32_t io_num = BUTTON_PIN;
    static int last = 1, cur = 1;
    while (1)
    {
        xNextWakeTime = xTaskGetTickCount();
        button_reading(BUTTON_IDX);
        vTaskDelayUntil(&xNextWakeTime, 10 / portTICK_PERIOD_MS);
    }
}

void buttonPressedHandle(void *pvParameters)
{
    while (1)
    {
        if (button_pressed(BUTTON_IDX))
        {
            reset_button_flag(BUTTON_IDX);
            printf("ESP32\r\n");
        }
    }
}

void app_main(void)
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    BTN_INIT(BUTTON_PIN, BUTTON_IDX);

    xTaskCreate(printStudentID, "CyclicTask", 2048, NULL, 1, NULL);
    xTaskCreate(buttonRead, "ButtonRead", 2048, NULL, 2, NULL);
    xTaskCreate(buttonPressedHandle, "ButtonPressedHandler", 2048, NULL, 2, NULL);

    while (1)
    {
    }
}