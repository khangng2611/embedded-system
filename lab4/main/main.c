#include <stdio.h>
#include <inttypes.h>
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/semphr.h"    

QueueHandle_t xMyQueue;

typedef enum {
    ePrintA = 0,
    ePrintMSG,
    ePrint123,
    eFaulty,
} eTaskCMD_t;

typedef struct TASK_COMMANDS
{
eTaskCMD_t eTaskCMD;
void *pvData;
} TaskCMD_t;

volatile uint32_t ulIdleCycleCount = 0UL;
static const char *pcMSG = "Hello, world!\r\n";
static const eTaskCMD_t eRequestArray[] = {ePrint123, ePrintA, ePrint123, ePrintMSG, eFaulty, ePrintA};



void vApplicationIdleHook ( void )
{
    ulIdleCycleCount++;
}

static void vSenderTask(void *pvParameters) 
{
    TaskCMD_t xTaskCMDStruct;
    BaseType_t xStatus;

    for ( ; ; ) {
        // eTaskCMD_t randomCMD = rand() % 3;
        // xTaskCMDStruct.eTaskCMD = randomCMD;
        int arrLen = sizeof(eRequestArray) / sizeof(eTaskCMD_t);
        for (int i = 0; i < arrLen; i++) {
            xTaskCMDStruct.eTaskCMD = eRequestArray[i];
            if (xTaskCMDStruct.eTaskCMD == ePrintMSG)
                xTaskCMDStruct.pvData = ( void * ) pcMSG;
            else
                xTaskCMDStruct.pvData = NULL;

            xStatus = xQueueSendToBack(xMyQueue, &xTaskCMDStruct, 0);

            if (xStatus != pdPASS) {
                printf( "Could not send to the queue.\r\n" );
            } 

        }

        vTaskDelay(portMAX_DELAY);
    }
}

static void vReceiverTask1( void * pvParameters) 
{
    TaskCMD_t xReceivedTaskCMDStruct;
    BaseType_t xStatus;
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

    for ( ; ; ) {
        xStatus = xQueueReceive(xMyQueue, &xReceivedTaskCMDStruct, xTicksToWait);

        if (xStatus == pdPASS) {
            if (xReceivedTaskCMDStruct.eTaskCMD == ePrintA)
                printf("%s prints A\r\n", pcTaskName);
            else if (xReceivedTaskCMDStruct.eTaskCMD > ePrint123)
                printf("Faulty Command\r\n");
            else 
                xStatus = xQueueSendToBack(xMyQueue, &xReceivedTaskCMDStruct, 0);
        } 
        // else {
        //     printf("Could not receive from the queue.\r\n");
        // }
    }
}

static void vReceiverTask2( void * pvParameters) 
{
    TaskCMD_t xReceivedTaskCMDStruct;
    BaseType_t xStatus;
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

    for ( ; ; ) {
        xStatus = xQueueReceive(xMyQueue, &xReceivedTaskCMDStruct, xTicksToWait);

        if (xStatus == pdPASS) {
            if (xReceivedTaskCMDStruct.eTaskCMD == ePrintMSG)
                printf("%s prints %s", pcTaskName, ( char * ) xReceivedTaskCMDStruct.pvData);
            else if (xReceivedTaskCMDStruct.eTaskCMD > ePrint123)
                printf("Faulty Command\r\n");
            else 
                xStatus = xQueueSendToBack(xMyQueue, &xReceivedTaskCMDStruct, 0);
        } 
        // else {
        //     printf("Could not receive from the queue.\r\n");
        // }
    }
}

static void vReceiverTask3( void * pvParameters) 
{
    TaskCMD_t xReceivedTaskCMDStruct;
    BaseType_t xStatus;
    char *pcTaskName;
    pcTaskName = ( char * ) pvParameters;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );

    for ( ; ; ) {
        xStatus = xQueueReceive(xMyQueue, &xReceivedTaskCMDStruct, xTicksToWait);

        if (xStatus == pdPASS) {
            if (xReceivedTaskCMDStruct.eTaskCMD == ePrint123)
                printf("%s print: 123\r\n", pcTaskName);
            else if (xReceivedTaskCMDStruct.eTaskCMD > ePrint123)
                printf("Faulty Command\r\n");
            else {
                xStatus = xQueueSendToBack(xMyQueue, &xReceivedTaskCMDStruct, 0);
            }
        } 
        // else {
        //     printf("Could not receive from the queue.\r\n");
        // }
    }
}



void app_main(void)
{
    xMyQueue = xQueueCreate(5, sizeof(TaskCMD_t));
    srand((int) time(0));

    if( xMyQueue != NULL ) {
        xTaskCreate( vReceiverTask1, "Receiver1", 3072, ( void * ) "Receiver1", 2, NULL );
        xTaskCreate( vReceiverTask2, "Receiver2", 3072, ( void * ) "Receiver2", 2, NULL );
        xTaskCreate( vReceiverTask3, "Receiver3", 3072, ( void * ) "Receiver3", 2, NULL );

        xTaskCreate( vSenderTask, "Sender1", 3072, NULL, 1, NULL );
        // xTaskCreate( vSenderTask, "Sender2", 3072, ( void * ) 200, 1, NULL );
        // xTaskCreate( vSenderTask, "Sender3", 3072, ( void * ) 300, 1, NULL );
    } else {
        printf("Failed to create queue.\r\n");
    }
}
