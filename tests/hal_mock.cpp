#include "hal_mock.h"
#include "targets/main.h"

UART_HandleTypeDef* HALMock::HAL_UART_Transmit_huart;
uint8_t* HALMock::HAL_UART_Transmit_pData;
uint16_t HALMock::HAL_UART_Transmit_Size;
uint32_t HALMock::HAL_UART_Transmit_Timeout;
ADC_HandleTypeDef HALMock::HAL_ADC_Start_hadc;
ADC_HandleTypeDef HALMock::HAL_ADC_PollForConversion_hadc;
ADC_HandleTypeDef HALMock::HAL_ADC_PollForConversion_timeout;
ADC_HandleTypeDef HALMock::HAL_ADC_GetValue_hadc;

void HALMock::HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout) {
    HAL_UART_Transmit_huart = huart;
    HAL_UART_Transmit_pData = pData;
    HAL_UART_Transmit_Size = Size;
    HAL_UART_Transmit_Timeout = Timeout;
}

HAL_StatusTypeDef HALMock::HAL_ADC_Start(ADC_HandleTypeDef* hadc) {
    HAL_ADC_Start_hadc = *hadc;
    return 1;
}

HAL_StatusTypeDef HALMock::HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout) {
    HAL_ADC_PollForConversion_hadc = *hadc;
    HAL_ADC_PollForConversion_timeout = Timeout;
    return 1;
}
uint32_t HALMock::HAL_ADC_GetValue(ADC_HandleTypeDef* hadc) {
    HAL_ADC_GetValue_hadc = *hadc;
    return (float)*hadc * 200;
}