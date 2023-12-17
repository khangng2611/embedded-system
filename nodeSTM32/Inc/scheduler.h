/*
 * scheduler.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Acer
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"
#include "main.h"
#include <stdint.h>

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
    struct sTask *pNext;
	uint32_t TaskID;
}sTask;

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

void SCH_Init(void);

unsigned char SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete_Task(const unsigned char INDEX);

#endif /* INC_SCHEDULER_H_ */
