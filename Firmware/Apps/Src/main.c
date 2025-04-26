#include "stm32xx_hal.h"
#include "Amperes.h"

int main() {
    HAL_Init();
    SystemClock_Config();

    // LED for debug
    GPIO_InitTypeDef led_config = {
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Pin = GPIO_PIN_5
    };
    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable clock for GPIOA
    HAL_GPIO_Init(GPIOA, &led_config); // initialize GPIOA with led_config

    // Testing init and get reading
    if (Amperes_Init() != INIT_OK) return 0;
    if (Amperes_Update() != UPDATE_OK) return 0;

    while(1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
    
    return 0;
}
