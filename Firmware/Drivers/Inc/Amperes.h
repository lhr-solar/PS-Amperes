#include "stm32xx_hal.h"
#include "ADC.h"
#include "CAN.h"

/**
 * Firmware for Amperes Board
 * STM32L431CBT
 * ADC is PA1
 */

#ifdef STM32L4xx
#define AMPERES_CHANNEL ADC_CHANNEL_6
#define AMPERES_SAMPLE_TIME ADC_SAMPLETIME_2CYCLES_5
#define AMPERES_ADC_PIN 1
#endif

#ifdef STM32F4xx
#define AMPERES_CHANNEL ADC_CHANNEL_1
#define AMPERES_SAMPLE_TIME ADC_SAMPLETIME_3CYCLES
#endif

extern StaticTask_t amperes_task_buffer;
extern StackType_t amperes_task_stack[configMINIMAL_STACK_SIZE];

typedef enum AmperesStatus {
    INIT_OK,
    INIT_FAIL,
    READING_OK,
    READING_FAIL
} AmperesStatus_t;

AmperesStatus_t Amperes_Init();
AmperesStatus_t Amperes_GetReading(uint32_t *reading);
void Amperes_Task(void *pvParameters);