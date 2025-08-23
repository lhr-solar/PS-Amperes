#include "Tasks.h"

void Task_Init() {
    // Init Amperes Task
    Amperes_Init();
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