#include "stm32xx_hal.h"
#include "Amperes.h"
#include "Tasks.h"

StaticTask_t Task_Init_Buffer;
StackType_t Task_Init_Stack_Array[TASK_INIT_STACK_SIZE];

int main() {
    HAL_Init();
    SystemClock_Config();

    // Initializing
    if (Amperes_Init() != INIT_OK) error_handler();

    // Init tasks
    xTaskCreateStatic(
        Task_Init,
        "Task init",
        configMINIMAL_STACK_SIZE,
        (void*)NULL,
        TASK_INIT_PRIO,
        Task_Init_Stack_Array,
        &Task_Init_Buffer
    );

    vTaskStartScheduler();

    // Should not reach here
    error_handler();
    while(1) {}

    return 0;
}
