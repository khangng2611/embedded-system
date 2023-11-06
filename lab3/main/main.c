#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "include/button.h"

#define BUTTON_PIN GPIO_NUM_4
#define BUTTON_IDX 0

static const char * pcTextForTask1 = "Task 1 Preempts \r\n";
static const char * pcTextForTask2 = "Task 2 is running \r\n";

SemaphoreHandle_t xSemaphore = NULL;
volatile uint32_t ulIdleCycleCount = 0UL;
TaskHandle_t task1;



void vPreemptFunction() 
{
    for( ; ;){
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
        {
            printf("current tick: %ld, %s", ulIdleCycleCount, pcTextForTask1);

            gpio_intr_disable(BUTTON_PIN);
            while (!gpio_get_level(BUTTON_PIN)){
                vTaskDelay( 5 / portTICK_PERIOD_MS );
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
            gpio_intr_enable(BUTTON_PIN);
        }
    }
}

void IRAM_ATTR Button_ISR()
{
    xSemaphoreGiveFromISR(xSemaphore, NULL);
}

void vApplicationIdleHook ( void )
{
    ulIdleCycleCount++;
    printf( "Idle\r\n");
}

void vTaskFunction ( void *pvParameters ) 
{
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;

    for( ; ; ) {
        // tickCount++;
        printf ( "current tick: %ld, %s", ulIdleCycleCount, pcTaskName );
        for(int ul = 0; ul < 0xfff; ul++ ) { }
        // vTaskDelay((1 / portTICK_PERIOD_MS) + 1);   
    }
}




void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary();
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);

    BTN_INIT(BUTTON_PIN, BUTTON_IDX);

    xTaskCreate ( vPreemptFunction , " Task 1", 3072 ,
                    ( void *) pcTextForTask1 , uxTaskPriorityGet(NULL) + 1, &task1 );

    TaskHandle_t task2;
    xTaskCreate ( vTaskFunction , " Task 2", 3072 ,
                    ( void *) pcTextForTask2 , 0, &task2 );

    gpio_install_isr_service(0);

    gpio_isr_handler_add(BUTTON_PIN, Button_ISR, NULL);
}
