#include "Tasks.h"

// For amperes
StaticTask_t amperes_task_buffer;
StackType_t  amperes_task_stack[configMINIMAL_STACK_SIZE];

void Task_Init() {
    // Init Amperes: ADC and CAN
    if (Amperes_Init() == AMPERES_INIT_FAIL) error_handler();

    // Init Amperes Task
    xTaskCreateStatic(
        Amperes_Task,
        "Amperes Task",
        configMINIMAL_STACK_SIZE,
        (void*) 1,
        AMPERES_PRIO,
        amperes_task_stack,
        &amperes_task_buffer
    );

   // Delete Init Task
    vTaskDelete(NULL);
}