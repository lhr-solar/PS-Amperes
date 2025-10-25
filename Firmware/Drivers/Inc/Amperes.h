#ifndef AMPERES_H
#define AMPERES_H

#include "common.h"
#include "ADC.h"
#include "CAN.h"

/**
 * Driver for Amperes Board (STM32L431CBT6)
 * - Receive data from ADC
 * - Send data over CAN
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

typedef enum AmperesStatus {    // TODO: better states
    READING_OK,
    READING_FAIL
} AmperesStatus_t;

/**
 * @brief Initializes ADC and CAN for Amperes
 */
bool Amperes_Init();

/**
 * @brief Get reading from ADC
 * @param reading Variable to hold reading
 * @retval Status: Fail, Ok (TODO: )
 */
AmperesStatus_t Amperes_GetReading(int32_t *reading);

/**
 * @brief Send reading over CAN
 */
AmperesStatus_t Amperes_SendCAN();

#endif // AMPERES_H