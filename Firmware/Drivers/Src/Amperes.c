#include "Amperes.h"

static ADC_HandleTypeDef amperes_adc = {0};
static ADC_InitTypeDef init = {0};
static QueueHandle_t amperes_q;

AmperesStatus_t Amperes_Init() {
    HAL_ADC_MspInit(&amperes_adc);

    #ifdef STM32L4xx
    // ADC Handle
    amperes_adc.Instance = ADC1;
    // ADC Init
    init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    init.Resolution = ADC_RESOLUTION_12B;
    init.DataAlign = ADC_DATAALIGN_RIGHT;
    init.ScanConvMode = ADC_SCAN_DISABLE;
    init.EOCSelection = ADC_EOC_SINGLE_CONV;
    init.LowPowerAutoWait = DISABLE;
    init.ContinuousConvMode = DISABLE;
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
    amperes_adc.Instance = ADC1;
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

    if (adc_init(init, &amperes_adc) != ADC_OK) return INIT_FAIL;

    return INIT_OK;
}

AmperesStatus_t Amperes_Update() {
    if (adc_read(AMPERES_CHANNEL, AMPERES_SAMPLE_TIME, &amperes_adc, &amperes_q) != ADC_OK) {
        return UPDATE_FAIL;
    }
    return UPDATE_OK;
}

uint32_t Amperes_GetReading() {
    uint32_t reading = 0;
    if (xQueueReceive(amperes_q, &reading, portMAX_DELAY) == pdPASS) {
        return reading;
    }
    
    // TO DO: what to return on error
    return reading;
}