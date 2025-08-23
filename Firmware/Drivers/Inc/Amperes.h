#ifndef AMPERES_H
#define AMPERES_H

#include "common.h"
#include "ADC.h"
#include "CAN.h"

/**
 * Firmware for Amperes Board
 * STM32L431CBT
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

#define ADC_PORT GPIOA
#define ADC_PIN GPIO_PIN_1

typedef enum AmperesStatus {
    INIT_OK,
    INIT_FAIL,
    READING_OK,
    READING_FAIL
} AmperesStatus_t;

/**
 * @brief 
 */
AmperesStatus_t Amperes_Init();

/**
 * @brief 
 */
AmperesStatus_t Amperes_GetReading(uint32_t *reading);


#endif // AMPERES_H