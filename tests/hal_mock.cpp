#include "hal_mock.h"
#include "targets/main.h"

ADC_HandleTypeDef Mock_HAL_ADC::HAL_ADC_Start_hadc = -1;
ADC_HandleTypeDef Mock_HAL_ADC::HAL_ADC_PollForConversion_hadc = -1;
uint32_t Mock_HAL_ADC::HAL_ADC_PollForConversion_timeout = UINT32_MAX;
ADC_HandleTypeDef Mock_HAL_ADC::HAL_ADC_GetValue_hadc = -1;

UART_HandleTypeDef Mock_HAL_UART::HAL_UART_Transmit_huart = -1;
uint8_t Mock_HAL_UART::HAL_UART_Transmit_pData[MOCK_BUFFER_SIZE+1] = {UINT8_MAX};
uint16_t Mock_HAL_UART::HAL_UART_Transmit_Size = UINT16_MAX;
uint32_t Mock_HAL_UART::HAL_UART_Transmit_Timeout = UINT32_MAX;
UART_HandleTypeDef Mock_HAL_UART::HAL_UART_Receive_IT_huart = -1;    
uint8_t Mock_HAL_UART::HAL_UART_Receive_IT_pData[MOCK_BUFFER_SIZE+1] = {UINT8_MAX};
uint16_t Mock_HAL_UART::HAL_UART_Receive_IT_Size = UINT16_MAX;

void Mock_HAL_ADC::reset() {
    HAL_ADC_Start_hadc = -1;
    HAL_ADC_PollForConversion_hadc = -1;
    HAL_ADC_PollForConversion_timeout = UINT32_MAX;
    HAL_ADC_GetValue_hadc = -1;
}

HAL_StatusTypeDef Mock_HAL_ADC::HAL_ADC_Start(ADC_HandleTypeDef* hadc) {
    HAL_ADC_Start_hadc = *hadc;
    return 1;
}

HAL_StatusTypeDef Mock_HAL_ADC::HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout) {
    HAL_ADC_PollForConversion_hadc = *hadc;
    HAL_ADC_PollForConversion_timeout = Timeout;
    return 1;
}
uint32_t Mock_HAL_ADC::HAL_ADC_GetValue(ADC_HandleTypeDef* hadc) {
    HAL_ADC_GetValue_hadc = *hadc;
    return (float)*hadc * 200;
}

void Mock_HAL_UART::reset() {
    HAL_UART_Transmit_huart = -1;
    for(auto i = 0; i < MOCK_BUFFER_SIZE+1; i++) {
        HAL_UART_Transmit_pData[i] = UINT8_MAX;
        HAL_UART_Receive_IT_pData[i] = UINT8_MAX;
    }
    HAL_UART_Transmit_Size = UINT16_MAX;
    HAL_UART_Transmit_Timeout = UINT32_MAX;
    HAL_UART_Receive_IT_huart = -1;    
    HAL_UART_Receive_IT_Size = UINT16_MAX;
}

HAL_StatusTypeDef Mock_HAL_UART::HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    HAL_UART_Transmit_huart = *huart;
    for(auto i = 0; i < Size; i++)
        HAL_UART_Transmit_pData[i] = pData[i];
    // HAL_UART_Transmit_pData = (uint8_t*) pData;
    HAL_UART_Transmit_Size = Size;
    HAL_UART_Transmit_Timeout = Timeout;
    return 1;
}

HAL_StatusTypeDef Mock_HAL_UART::HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size) {
    HAL_UART_Receive_IT_huart = *huart;
    // HAL_UART_Receive_IT_pData = (uint8_t*) pData;
    for(auto i = 0; i < Size; i++)
        HAL_UART_Receive_IT_pData[i] = pData[i];
    HAL_UART_Receive_IT_Size = Size;
    return 1;
}
