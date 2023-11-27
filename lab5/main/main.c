    #include <stdio.h>
    #include <inttypes.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include <stdlib.h>
    #include "driver/gpio.h"
    #include "freertos/semphr.h"
    #include "include/button.h"
    #include "freertos/timers.h"


  /* The periods assigned to the one-shot and auto-reload timers are 3.333 second and half a 
second respectively. */
#define TIMER1_PERIOD pdMS_TO_TICKS(2000) // Which can be used for printing ahihi
#define TIMER2_PERIOD pdMS_TO_TICKS(3000) // Which can be used for printing ihaha
#define TIMER1_COUNT 10
#define TIMER2_COUNT 5
volatile uint32_t ulIdleCycleCount = 0UL;
volatile uint32_t ulCallCount = 0UL;
TimerHandle_t xTimer1Printing, xTimer2Printing;

void vApplicationIdleHook ( void )
{
    ulIdleCycleCount++;
}

// static void prvOneShotTimerCallback( TimerHandle_t xTimer )
// {
//     TickType_t xTimeNow;
//  /* Obtain the current tick count. */
//     xTimeNow = xTaskGetTickCount();
//  /* Output a string to show the time at which the callback was executed. */
//     // printf( "One-shot timer callback executing", xTimeNow );
//     printf( "One-shot timer callback executing %ld \n \r ", xTimeNow );
//  /* File scope variable. */
//     ulCallCount++;
// }

// static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
// {
//     TickType_t xTimeNow;
//     /* Obtain the current tick count. */
//      xTimeNow = xTaskGetTickCount();
//      /* Output a string to show the time at which the callback was executed. */
//     // printf( "Auto-reload timer callback executing", xTimeNow );
//      printf( "Auto-reload timer callback executing /%ld \n \r ", xTimeNow );
//     ulCallCount++;
// }

//     static void prvTimerCallback( TimerHandle_t xTimer )
//         {
//             TickType_t xTimeNow;
//             uint32_t ulExecutionCount;
//             /* A count of the number of times this software timer has expired is stored in the timer's 
//             ID. Obtain the ID, increment it, then save it as the new ID value. The ID is a void 
//              pointer, so is cast to a uint32_t. */
//             ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
//             ulExecutionCount++;
//             vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );
//             /* Obtain the current tick count. */
//             xTimeNow = xTaskGetTickCount();
//             /* The handle of the one-shot timer was stored in xOneShotTimer when the timer was created. 
//             Compare the handle passed into this function with xOneShotTimer to determine if it was the 
//             one-shot or auto-reload timer that expired, then output a string to show the time at which 
//             the callback was executed. */
//             if( xTimer == xOneShotTimer )
//             {
//                  printf( "One-shot timer callback executing %ld \r\n", xTimeNow );
//             }
//             else
//             {
//             /* xTimer did not equal xOneShotTimer, so it must have been the auto-reload timer that
//             expired. */
//                 printf( "Auto-reload timer callback executing %ld \r\n", xTimeNow );
//                 if( ulExecutionCount == 5 )
//                  {
//             /* Stop the auto-reload timer after it has executed 5 times. This callback function 
//  executes in the context of the RTOS daemon task so must not call any functions that 
//  might place the daemon task into the Blocked state. Therefore a block time of 0 is 
//  used. */
//                     xTimerStop( xTimer, 0 );
//                 }
//             }
// }

// static void prvAutoReloadTimerCallback( TimerHandle_t xTimer ){
//     TickType_t xTimeNow;
//  /* Obtain the current tick count. */
//     xTimeNow = xTaskGetTickCount();
//  /* Output a string to show the time at which the callback was executed. */
//     // printf( "One-shot timer callback executing", xTimeNow );
//     printf( "One-shot timer callback executing %ld \n \r ", xTimeNow );
//  /* File scope variable. */
//     ulCallCount++;
// }

// static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
// {
//     TickType_t xTimeNow;
//     /* Obtain the current tick count. */
//      xTimeNow = xTaskGetTickCount();
//      /* Output a string to show the time at which the callback was executed. */
//     // printf( "Auto-reload timer callback executing", xTimeNow );
//      printf( "Auto-reload timer callback executing /%ld \n \r ", xTimeNow );
//     ulCallCount++;
// }

static void prvTimerCallback( TimerHandle_t xTimer )
        {
            TickType_t xTimeNow;
            uint32_t ulExecutionCount;
            /* A count of the number of times this software timer has expired is stored in the timer's 
            ID. Obtain the ID, increment it, then save it as the new ID value. The ID is a void 
             pointer, so is cast to a uint32_t. */
            ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
            ulExecutionCount++;
            vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );

            /* Obtain the current tick count. */
            xTimeNow = xTaskGetTickCount();
          if( xTimer == xTimer1Printing){
                printf("print Ahihi %ld \r\n", xTimeNow);
                if( ulExecutionCount >= TIMER1_COUNT){
                    xTimerStop( xTimer, 0);
                    printf("Timer 1 stopped \n");
                }
          }
          else if( xTimer == xTimer2Printing){ // Print ihaha 
            printf("print iHaha %ld \r\n", xTimeNow);
            if( ulExecutionCount >= TIMER2_COUNT)
            {
                    xTimerStop( xTimer, 0);
                    printf("Timer 2 stopped \n");
            }
          }        
}

void app_main(void)
{
    BaseType_t xTimer1Started, xTimer2Started;
    /* Create the Printing ahihi timer, storing the handle to the created timer in  xTimer1Printing. */
     xTimer1Printing = xTimerCreate("PrintAhihi", TIMER1_PERIOD, pdTRUE, 0, prvTimerCallback); 

    /* Create the Printing ihaha timer, storing the handle to the created timer in  xTimer2Printing. */
     xTimer2Printing = xTimerCreate("PrintiHaha", TIMER2_PERIOD, pdTRUE, 0, prvTimerCallback); 
    /* Check the software timers were created. */
    if( ( xTimer1Printing != NULL ) && ( xTimer2Printing != NULL ) )
    {
        xTimer1Started = xTimerStart( xTimer1Printing, 0 );
        xTimer2Started = xTimerStart( xTimer2Printing, 0 );
    }
}

