#include "common.h"

void error_handler() {
    // Turn off LED
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    while (1) {

    }
}

void success_handler() {
    // Blink LED
    while(1){
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}
