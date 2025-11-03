#ifndef TASKS_H
#define TASKS_H
#include "Amperes.h"

/* Task Generation Macro 
// #define FOR_EACH_TASK(TASK, PRIO, STACK_SIZE)   \
//     extern StaticTask_t  TASK_##task_buffer;    \
//     extern StackType_t TASK_##task_stack[STACK_SIZE];   \
//     #define TASK_
*/

/* Amperes Task */
extern StaticTask_t amperes_task_buffer;
extern StackType_t  amperes_task_stack[configMINIMAL_STACK_SIZE];
#define AMPERES_PRIO    1
#define AMPERES_DELAY   pdMS_TO_TICKS(200)     // TODO

/**
 * @brief Amperes Task: TODO
 * @retval none
 */
void Amperes_Task(void *pvParameters);


/* Init Task */
#define TASK_INIT_PRIO          tskIDLE_PRIORITY + 1
#define TASK_INIT_STACK_SIZE    configMINIMAL_STACK_SIZE

/**
 * @brief Initializes all tasks
 * @retval none
 */
void Task_Init();

#endif
