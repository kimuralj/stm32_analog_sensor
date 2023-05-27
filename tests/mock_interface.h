#ifndef __MOCK_INTERFACE_H__
#define __MOCK_INTERFACE_H__

#include <stdint.h>
#include "hal_mock.h"

auto HAL_UART_Transmit = [](UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout){ HALMock::HAL_UART_Transmit(huart, pData, Size, Timeout);};
auto HAL_ADC_Start = [](ADC_HandleTypeDef* hadc){ return HALMock::HAL_ADC_Start(hadc);};
auto HAL_ADC_PollForConversion = [](ADC_HandleTypeDef* hadc, uint32_t Timeout){ return HALMock::HAL_ADC_PollForConversion(hadc, Timeout);};
auto HAL_ADC_GetValue = [](ADC_HandleTypeDef* hadc){ return HALMock::HAL_ADC_GetValue(hadc);};

#endif