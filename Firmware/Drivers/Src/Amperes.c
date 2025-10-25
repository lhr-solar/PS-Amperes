#include "Amperes.h"

/** =======================================================
 *  ADC Queue
 * ======================================================= */
// TODO: why size
#ifndef ADC_QUEUE_LENGTH
    #define ADC_QUEUE_LENGTH 100    
#endif
#define ITEM_SIZE sizeof( uint32_t )

QueueHandle_t amperes_q;
uint8_t qStorage[ADC_QUEUE_LENGTH * ITEM_SIZE];
static StaticQueue_t xStaticQueue;


/**
 * @brief Override MSP GPIO init
 */
void HAL_ADC_MspGPIOInit(ADC_HandleTypeDef* hadc) {
    // Initialize PA1 for ADC
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

    __HAL_RCC_GPIOA_CLK_ENABLE();
}


static bool Amperes_ADC_Init() {
    // Initialize queue
    amperes_q = xQueueCreateStatic(ADC_QUEUE_LENGTH, ITEM_SIZE, qStorage, &xStaticQueue);

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
    
    volatile adc_status_t s = adc_init(init, hadc1);
    s+=0;
    if (adc_init(init, hadc1) != ADC_OK) error_handler();

    // Initialize ADC
    // if (adc_init(init, hadc1) != ADC_OK) return false;  // or call error handler?

    // Debug
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

    return true;
}

// static bool Amperes_CAN_Init() {
//     // Create filter
//     CAN_FilterTypeDef  sFilterConfig;
//     sFilterConfig.FilterBank = 0;
//     sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
//     sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
//     sFilterConfig.FilterIdHigh = 0x0000;
//     sFilterConfig.FilterIdLow = 0x0000;
//     sFilterConfig.FilterMaskIdHigh = 0x0000;
//     sFilterConfig.FilterMaskIdLow = 0x0000;
//     sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
//     sFilterConfig.FilterActivation = ENABLE;
//     sFilterConfig.SlaveStartFilterBank = 14;

//     // setup can1 init
//     hcan1->Init.Prescaler = 5;
//     hcan1->Init.Mode = CAN_MODE_LOOPBACK;
//     hcan1->Init.SyncJumpWidth = CAN_SJW_1TQ;
//     hcan1->Init.TimeSeg1 = CAN_BS1_6TQ;
//     hcan1->Init.TimeSeg2 = CAN_BS2_2TQ;
//     hcan1->Init.TimeTriggeredMode = DISABLE;
//     hcan1->Init.AutoBusOff = DISABLE;
//     hcan1->Init.AutoWakeUp = DISABLE;
//     hcan1->Init.AutoRetransmission = ENABLE;
//     hcan1->Init.ReceiveFifoLocked = DISABLE;

//     // If TransmitFifoPriority is disabled, the hardware selects the mailbox based on the message ID priority. 
//     // If enabled, the hardware uses a FIFO mechanism to select the mailbox based on the order of transmission requests.
//     hcan1->Init.TransmitFifoPriority = ENABLE;

//     // initialize CAN1
//     if (can_init(hcan1, &sFilterConfig) != CAN_OK) return false;    // or call error handler?

//     // Debug

    
//     return true;
// }


bool Amperes_Init() {
    // Init ADC
    if (!Amperes_ADC_Init()) return false;

    // Init CAN
    // if (!Amperes_CAN_Init()) return false;

    // Start CAN
    // if (can_start(hcan1) != CAN_OK) return false;

    return true;
}


AmperesStatus_t Amperes_GetReading(int32_t *reading) {
    if (adc_read(AMPERES_CHANNEL, AMPERES_SAMPLE_TIME, hadc1, &amperes_q) != ADC_OK) {
        return READING_FAIL;
    }
    if (xQueueReceive(amperes_q, reading, 0) == pdPASS) {
        return READING_OK;
    }
    return READING_FAIL;
}