#include "stm32xx_hal.h"
#include "ADC.h"

/**
 * Drivers for the Amperes Board
 * ADC is PA1
 */

#ifdef STM32L4xx
#define AMPERES_CHANNEL ADC_CHANNEL_6
#define AMPERES_SAMPLE_TIME ADC_SAMPLETIME_2CYCLES_5
#endif

#ifdef STM32F4xx
#define AMPERES_CHANNEL ADC_CHANNEL_1
#define AMPERES_SAMPLE_TIME ADC_SAMPLETIME_3CYCLES
#endif

typedef enum AmperesStatus {
    INIT_OK,
    INIT_FAIL,
    UPDATE_OK,
    UPDATE_FAIL
} AmperesStatus_t;

AmperesStatus_t Amperes_Init();
AmperesStatus_t Amperes_Update();
uint32_t Amperes_GetReading();