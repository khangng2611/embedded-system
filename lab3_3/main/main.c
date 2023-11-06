#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/semphr.h"    
#include "include/button.h"

#define BUTTON_PIN GPIO_NUM_0
#define BUTTON_IDX 0

static const char * pcTextForTask1 = "Task 1 is running \r\n";
static const char * pcTextForTask2 = "Task 2 is running \r\n";
static const char * pcTextForTask3 = "Task 3 is running \r\n";

SemaphoreHandle_t xSemaphore = NULL;
volatile uint32_t ulIdleCycleCount = 0UL;
TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;



void vApplicationIdleHook ( void )
{
    ulIdleCycleCount++;
}

void vTask1Function() 
{
    for( ; ;){
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
        {
            // tickCount++;
            printf("current tick: %ld, %s", ulIdleCycleCount, pcTextForTask1);

            gpio_intr_disable(BUTTON_PIN);
            while (!gpio_get_level(BUTTON_PIN)){
                vTaskDelay( 5 / portTICK_PERIOD_MS );
            }
            // vTaskDelay(10 / portTICK_PERIOD_MS);
            gpio_intr_enable(BUTTON_PIN);
        }
    }
}

void IRAM_ATTR Button_ISR()
{
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}


void vTask2Function ( void *pvParameters ) 
{
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    TickType_t tickToWait = pdMS_TO_TICKS(30);

    for( ; ; ) {
        printf ( "current tick: %ld, %s", ulIdleCycleCount, pcTaskName );
        vTaskDelay(tickToWait);
    }
}

void vTask3Function ( void *pvParameters ) 
{
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    int32_t count = 0;

    for( ; ; ) {
        count++;
        printf ( "current count: %ld, %s", count, pcTaskName );
        if (count == 300) {
            count = 0;
            vPortYield();
        }
        for(int ul = 0; ul < 0xfff; ul++ ) { }
    }
}



void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary();
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);

    BTN_INIT(BUTTON_PIN, BUTTON_IDX);

    xTaskCreate ( vTask3Function , " Task 3", 3072 ,
                    ( void *) pcTextForTask3 , 0, &task3 );
    xTaskCreate ( vTask2Function , " Task 2", 3072 ,
                    ( void *) pcTextForTask2 , 4, &task2 );
    xTaskCreate ( vTask1Function , " Task 1", 3072 ,
                    ( void *) pcTextForTask1 , configMAX_PRIORITIES, &task1 );


    gpio_install_isr_service(0);

    gpio_isr_handler_add(BUTTON_PIN, Button_ISR, NULL);
}
