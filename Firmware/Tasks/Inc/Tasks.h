#ifndef TASKS_H
#define TASKS_H

/**
 * Tasks
 */

#include "Amperes.h"

/* Amperes Task */
extern StaticTask_t amperes_task_buffer;
extern StackType_t  amperes_task_stack[configMINIMAL_STACK_SIZE];
#define AMPERES_PRIO    1
#define AMPERES_DELAY   200     // TODO

/** @brief Amperes Task: TODO  */ 
void Amperes_Task(void *pvParameters);


/* Init Task */
extern StaticTask_t amperes_task_buffer;
extern StackType_t  amperes_task_stack[configMINIMAL_STACK_SIZE];
#define TASK_INIT_PRIO          tskIDLE_PRIORITY + 1
#define TASK_INIT_STACK_SIZE    configMINIMAL_STACK_SIZE

/** @brief Initialize all tasks */ 
void Task_Init();

#endif
