#include "Tasks.h"

void Amperes_Task(void *pvParameters) {
    while (1) {
        // Get ADC reading
        int32_t reading = 0;
        Amperes_GetReading(&reading);

        // Convert ADC value into current reading

        // Create CAN payload
        // CAN_TxHeaderTypeDef tx_header = {0};   
        // tx_header.StdId = 0x1;
        // tx_header.RTR = CAN_RTR_DATA;
        // tx_header.IDE = CAN_ID_STD;
        // tx_header.DLC = 2;
        // tx_header.TransmitGlobalTime = DISABLE;

        // Send ADC data over CAN
        // uint8_t tx_data[8] = {0};   // fit adc data in here
        // tx_data[0] = 0x01;
        // if (can_send(hcan1, &tx_header, tx_data, portMAX_DELAY) != CAN_SENT) ErrorHandler();

        // Debug
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

        // TODO: don't poll, block and wake up task instead
        vTaskDelay(AMPERES_DELAY);
    }
}
