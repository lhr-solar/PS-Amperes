#ifndef AMPERES_H
#define AMPERES_H

/** ==========================================================
 *  Driver for Amperes Board (STM32L431CBT6)
 *  ==========================================================
 *  - Receive data from ADC
 *  - Send data over CAN
 */

#include "common.h"
#include "ADC.h"
#include "CAN.h"


/** ================================================================
 *  ADC (12 bit)
 * ================================================================ */
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

// Reference voltage for bidirectional current reading (1.25V)
#define AMPERES_VREF 1.25

/**
 * @brief Convert ADC reading to current reading.
 * @n 
 *  - ADC to voltage: ADC * (3.3V / 4096)
 * @n 
 *  - Voltage to current: (V - Vref) / ((250 E-6 ohm)(100 V/V))
 * @param reading ADC value to be converted
 */
#define AMPERES_ADC_TO_CURRENT(reading) (((reading * (3.3 / 4096)) - AMPERES_VREF) / (0.025))



/** ================================================================
 *  Amperes Functions
 * ================================================================ */

typedef enum AmperesStatus {    // TODO: better states
    AMPERES_OK,
    AMPERES_INIT_FAIL,
    AMPERES_ADC_FAIL,
    AMPERES_QUEUE_FULL
} AmperesStatus_t;

/**
 * @brief Initializes ADC and CAN for Amperes
 * @retval Status: INIT_FAIL or OK
 */
AmperesStatus_t Amperes_Init();

/**
 * @brief Get reading from ADC
 * @param current_reading Variable to hold amperes reading 
 * @retval Status: ADC_FAIL, QUEUE_FULL, or OK
 */
AmperesStatus_t Amperes_GetReading(int32_t *current_reading);


/**
 * @brief Send reading over CAN
 */
AmperesStatus_t Amperes_SendCAN(uint32_t reading);

#endif // AMPERES_H