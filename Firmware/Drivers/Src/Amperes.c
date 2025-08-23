#include "Amperes.h"

// Task
StaticTask_t amperes_task_buffer;
StackType_t amperes_task_stack[configMINIMAL_STACK_SIZE];

// Queue
#define QUEUE_LENGTH 100    // TODO: reasoning
#define ITEM_SIZE   sizeof( uint32_t )

QueueHandle_t amperes_q;
uint8_t qStorage[QUEUE_LENGTH * ITEM_SIZE];
static StaticQueue_t xStaticQueue;


/**
 * Overridde MSP GPIO init
 */
void HAL_ADC_MspGPIOInit(ADC_HandleTypeDef* hadc) {
    // Initialize PA1 for ADC
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef input =  {
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL, 
        .Pin = ADC_PIN
    };

    HAL_GPIO_Init(ADC_PORT, &input);

    // Initialize PA5 for LED debug
    GPIO_InitTypeDef led_config = {
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Pin = GPIO_PIN_5
    };
    HAL_GPIO_Init(GPIOA, &led_config);
}


AmperesStatus_t Amperes_Init() {
    // Initialize queue
    amperes_q = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, qStorage, &xStaticQueue);

    // Initialize CAN
    // ...

    // ADC init structure
    ADC_InitTypeDef init = {0};

    #ifdef STM32L4xx
    // ADC Handle
    // amperes_adc.Instance = ADC1;
    // ADC Init
    init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    init.Resolution = ADC_RESOLUTION_12B;
    init.DataAlign = ADC_DATAALIGN_RIGHT;
    init.ScanConvMode = ADC_SCAN_DISABLE;
    init.EOCSelection = ADC_EOC_SINGLE_CONV;
    init.LowPowerAutoWait = DISABLE;
    init.ContinuousConvMode = ENABLE;
    init.NbrOfConversion = 1;
    init.DiscontinuousConvMode = DISABLE;
    init.ExternalTrigConv = ADC_SOFTWARE_START;
    init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    init.DMAContinuousRequests = DISABLE;
    init.Overrun = ADC_OVR_DATA_PRESERVED;
    init.OversamplingMode = DISABLE;
    #endif

    #ifdef STM32F4xx
    // ADC Handle
    // amperes_adc.Instance = ADC1;
    // ADC Init
    init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    init.Resolution = ADC_RESOLUTION_12B;
    init.ScanConvMode = DISABLE;
    init.ContinuousConvMode = DISABLE;
    init.DiscontinuousConvMode = DISABLE;
    init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    init.ExternalTrigConv = ADC_SOFTWARE_START;
    init.DataAlign = ADC_DATAALIGN_RIGHT;
    init.NbrOfConversion = 1;
    init.DMAContinuousRequests = DISABLE;
    init.EOCSelection = ADC_EOC_SINGLE_CONV;
    #endif
    
    // Initialize ADC
    if (adc_init(init, hadc1) != ADC_OK) return INIT_FAIL;
    
    // Set LED for debug
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

    return INIT_OK;
}


AmperesStatus_t Amperes_GetReading(uint32_t *reading) {
    if (adc_read(AMPERES_CHANNEL, AMPERES_SAMPLE_TIME, hadc1, &amperes_q) != ADC_OK) {
        return READING_FAIL;
    }
    if (xQueueReceive(amperes_q, reading, 0) == pdPASS) {
        return READING_OK;
    }
    return READING_FAIL;
}


