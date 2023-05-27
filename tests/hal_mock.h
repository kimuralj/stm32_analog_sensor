#ifndef __HAL_MOCK__
#define __HAL_MOCK__

#include <stdint.h>

#define MOCK_BUFFER_SIZE		13

typedef int UART_HandleTypeDef;
typedef int GPIO_TypeDef;
typedef int ADC_HandleTypeDef;
typedef int HAL_StatusTypeDef;

class Mock_HAL_ADC {
public:
    static void reset();
    static ADC_HandleTypeDef HAL_ADC_Start_hadc;
    static HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);

    static ADC_HandleTypeDef HAL_ADC_PollForConversion_hadc;
    static uint32_t HAL_ADC_PollForConversion_timeout;
    static HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

    static ADC_HandleTypeDef HAL_ADC_GetValue_hadc;
    static uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);
};

class Mock_HAL_UART {
public:
    static void reset();
    static UART_HandleTypeDef HAL_UART_Transmit_huart;    
    static uint8_t HAL_UART_Transmit_pData[MOCK_BUFFER_SIZE+1];
    static uint16_t HAL_UART_Transmit_Size;
    static uint32_t HAL_UART_Transmit_Timeout;
    static HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);

    static UART_HandleTypeDef HAL_UART_Receive_IT_huart;    
    static uint8_t HAL_UART_Receive_IT_pData[MOCK_BUFFER_SIZE+1];
    static uint16_t HAL_UART_Receive_IT_Size;
    static HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
};


#endif