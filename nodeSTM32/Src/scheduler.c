/*
 * scheduler.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Acer
 */
#include "scheduler.h"
#define TICK 10

sTask SCH_tasks_G[SCH_MAX_TASKS];

sTask* head = NULL;

void SCH_Init(void){
    unsigned char i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
}
void SCH_Update(void){
	 unsigned char Index;
	    // NOTE: calculations are in *TICKS* (not milliseconds)
	    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
	        // Check if there is a task at this location
	        if (SCH_tasks_G[Index].pTask){
	            if (SCH_tasks_G[Index].Delay == 0) {
	                // The task is due to run
	                // Inc. the 'RunMe' flag
	                SCH_tasks_G[Index].RunMe += 1;
	                if (SCH_tasks_G[Index].Period) {
	                    // Schedule periodic tasks to run again
	                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
	                }
	            } else {
	                // Not yet ready to run: just decrement the delay
	                SCH_tasks_G[Index].Delay -= 1;
	            }
	        }
	    }
//	if(head != NULL){
//		head->Delay--;
//	}
}

unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	 	unsigned char Index = 0;
	    // First find a gap in the array (if there is one)
	    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
	    {
	       Index++;
	    }
	    // Have we reached the end of the list?
	    if (Index == SCH_MAX_TASKS)
	    {
	        return SCH_MAX_TASKS;
	    }
	    // If we're here, there is a space in the task array
	    SCH_tasks_G[Index].pTask = pFunction;
	    SCH_tasks_G[Index].Delay = DELAY/TICK;
	    SCH_tasks_G[Index].Period = PERIOD/TICK;
	    SCH_tasks_G[Index].RunMe = 0;
	    SCH_tasks_G[Index].TaskID = Index;
	    // return position of task (to allow later deletion)
	    return Index;

//	uint32_t index = 0;
//	uint8_t waiting = 0;
//	 while ((SCH_tasks_G[index].pTask != 0) && (index < SCH_MAX_TASKS)){
//		 index++;
//	 }
//	 if(index == SCH_MAX_TASKS){
//		 return SCH_MAX_TASKS;
//	 }
//	 SCH_tasks_G[index].pTask = pFunction;
//	 SCH_tasks_G[index].Period = PERIOD;
//	 SCH_tasks_G[index].TaskID = index;
//	 sTask* cur  = head;
//	 sTask* prev = NULL;
//	 // add in the head of list
//	 if(head == NULL){
//		 head = &SCH_tasks_G[index];
//		 SCH_tasks_G[index].Delay = DELAY;
//	 }else{
//		 while(cur != NULL){
//            waiting += cur->Delay;
//            if(waiting  > DELAY) break;
//            prev = cur;
//            cur = cur->pNext;
//		 }
//		 // add in the end of list
//		 if(cur == NULL){
//			prev->pNext = &SCH_tasks_G[index];
//			SCH_tasks_G[index].Delay = DELAY - waiting;
//		 }else{
//			 //add in the head of list
//			 if(cur == head){
//				 head = &SCH_tasks_G[index];
//				 head->pNext = cur;
//				 head->Delay = DELAY;
//			 }
//			 else{
//				 //add in the middle of list
//				 prev->pNext = &SCH_tasks_G[index];
//				 SCH_tasks_G[index].pNext = cur;
//				 SCH_tasks_G[index].Delay = DELAY - waiting + cur->Delay;
//			 }
//			 cur->Delay = waiting - SCH_tasks_G[index].Delay;
//		 }
//	 }
//	 return index;
}
void SCH_Dispatch_Tasks(void)
{
    unsigned char Index;
    // Dispatches (runs) the next task (if one is ready)
    for (Index = 0; Index < SCH_MAX_TASKS; Index++){
        if (SCH_tasks_G[Index].RunMe > 0) {
            (*SCH_tasks_G[Index].pTask)(); // Run the task
            SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
            // Periodic tasks will automatically run again
            // - if this is a 'one shot' task, remove it from the array
            if (SCH_tasks_G[Index].Period == 0)
            {
                SCH_Delete_Task(Index);
            }
        }
    }

//	if(head != NULL && head->Delay == 0){
//		// run task
//		(*head->pTask)();
//		if(head->Period != 0) SCH_Add_Task(head->pTask, head->Period, head->Period);
//		uint32_t del_index = head->TaskID;
//		head = head->pNext;
//		SCH_Delete_Task(del_index);
//	}
}
void SCH_Delete_Task(const unsigned char TASK_INDEX){
	if(SCH_tasks_G[TASK_INDEX].pTask == 0){
		return ;
	}
	else{
	    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	    SCH_tasks_G[TASK_INDEX].Delay = 0;
	    SCH_tasks_G[TASK_INDEX].Period = 0;
	    SCH_tasks_G[TASK_INDEX].pNext = 0;
	    SCH_tasks_G[TASK_INDEX].TaskID = 0;
	}
}
