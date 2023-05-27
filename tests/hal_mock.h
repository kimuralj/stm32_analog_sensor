#ifndef __HAL_MOCK__
#define __HAL_MOCK__

#include <stdint.h>

typedef int UART_HandleTypeDef;
typedef int GPIO_TypeDef;
typedef int ADC_HandleTypeDef;
typedef int HAL_StatusTypeDef;

class HALMock {
public:

    static UART_HandleTypeDef* HAL_UART_Transmit_huart;    
    static uint8_t* HAL_UART_Transmit_pData;
    static uint16_t HAL_UART_Transmit_Size;
    static uint32_t HAL_UART_Transmit_Timeout;

    static void HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

    static ADC_HandleTypeDef HAL_ADC_Start_hadc;
    static HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);

    static ADC_HandleTypeDef HAL_ADC_PollForConversion_hadc;
    static ADC_HandleTypeDef HAL_ADC_PollForConversion_timeout;
    static HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

    static ADC_HandleTypeDef HAL_ADC_GetValue_hadc;
    static uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);


};


#endif