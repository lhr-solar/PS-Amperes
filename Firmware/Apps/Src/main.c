#include "stm32xx_hal.h"
#include "Amperes.h"

uint32_t reading;

int main() {
    HAL_Init();
    SystemClock_Config();

    // Initializing
    if (Amperes_Init() != INIT_OK) return 0;

    // Task
    xTaskCreateStatic(Amperes_Task,
                    "Amperes Task",
                    configMINIMAL_STACK_SIZE,
                    (void*) 1,
                    tskIDLE_PRIORITY+4,
                    amperes_task_stack,
                    &amperes_task_buffer);

    vTaskStartScheduler();

    while(1) {}

    return 0;
}
