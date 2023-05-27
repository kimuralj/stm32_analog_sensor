#ifndef __HAL_MOCK__
#define __HAL_MOCK__

#include <stdint.h>


typedef int UART_HandleTypeDef;
typedef int ADC_HandleTypeDef;
typedef int HAL_StatusTypeDef;
typedef int GPIO_TypeDef;
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;

#define MOCK_BUFFER_SIZE		13


#define LD3_GPIO_Port ((GPIO_TypeDef *) 4)
#define LD3_Pin 3

#define READING_RATE	100
#define EVENT_CLICK		1

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

class Mock_HAL_GPIO {
public:
    static void reset();

    static uint32_t HAL_GetTick_counter;
    static uint32_t HAL_GetTick(void);

    static GPIO_TypeDef HAL_GPIO_ReadPin_GPIOx;
    static uint16_t HAL_GPIO_ReadPin_GPIO_Pin;
    static GPIO_PinState HAL_GPIO_ReadPin_return;
    static GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

    static GPIO_TypeDef HAL_GPIO_WritePin_GPIOx;
    static uint16_t HAL_GPIO_WritePin_GPIO_Pin;
    static GPIO_PinState HAL_GPIO_WritePin_PinState;
    static void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
};

#endif