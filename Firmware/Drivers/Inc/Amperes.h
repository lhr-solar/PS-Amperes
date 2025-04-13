#include "stm32xx_hal.h"
#include "ADC.h"

/**
 * Drivers for the Amperes Board
 */

typedef enum initStatus{
    INIT_OK,
    INIT_FAIL
} init_t;

init_t AmperesInit();
uint32_t updateAmperesMeasurement();