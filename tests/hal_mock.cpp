#include "hal_mock.h"
#include "targets/main.h"

ADC_HandleTypeDef  Mock_HAL_ADC::HAL_ADC_Start_hadc                             = -1;
ADC_HandleTypeDef  Mock_HAL_ADC::HAL_ADC_PollForConversion_hadc                 = -1;
uint32_t           Mock_HAL_ADC::HAL_ADC_PollForConversion_timeout              = UINT32_MAX;
ADC_HandleTypeDef  Mock_HAL_ADC::HAL_ADC_GetValue_hadc                          = -1;

UART_HandleTypeDef Mock_HAL_UART::HAL_UART_Transmit_huart                       = -1;
uint8_t            Mock_HAL_UART::HAL_UART_Transmit_pData[MOCK_BUFFER_SIZE+1]   = {UINT8_MAX};
uint16_t           Mock_HAL_UART::HAL_UART_Transmit_Size                        = UINT16_MAX;
uint32_t           Mock_HAL_UART::HAL_UART_Transmit_Timeout                     = UINT32_MAX;
UART_HandleTypeDef Mock_HAL_UART::HAL_UART_Receive_IT_huart                     = -1;    
uint8_t            Mock_HAL_UART::HAL_UART_Receive_IT_pData[MOCK_BUFFER_SIZE+1] = {UINT8_MAX};
uint16_t           Mock_HAL_UART::HAL_UART_Receive_IT_Size                      = UINT16_MAX;

uint32_t           Mock_HAL_GPIO::HAL_GetTick_counter                           = 0;
GPIO_PinState      Mock_HAL_GPIO::HAL_GPIO_ReadPin_return                       = GPIO_PIN_RESET;
GPIO_TypeDef       Mock_HAL_GPIO::HAL_GPIO_ReadPin_GPIOx                        = -1;
uint16_t           Mock_HAL_GPIO::HAL_GPIO_ReadPin_GPIO_Pin                     = -1;
GPIO_TypeDef       Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIOx                       = -1;
uint16_t           Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIO_Pin                    = -1;
GPIO_PinState      Mock_HAL_GPIO::HAL_GPIO_WritePin_PinState                    = GPIO_PIN_RESET;

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
    HAL_UART_Transmit_Size = Size;
    HAL_UART_Transmit_Timeout = Timeout;
    return 1;
}

HAL_StatusTypeDef Mock_HAL_UART::HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size) {
    HAL_UART_Receive_IT_huart = *huart;
    for(auto i = 0; i < Size; i++)
        HAL_UART_Receive_IT_pData[i] = pData[i];
    HAL_UART_Receive_IT_Size = Size;
    for(auto i = 0; i < Size; i++)
        pData[i] = HAL_UART_Transmit_pData[i];
    return 1;
}

void Mock_HAL_GPIO::reset() {
    HAL_GetTick_counter = 0;
    HAL_GPIO_ReadPin_GPIOx = -1;
    HAL_GPIO_ReadPin_GPIO_Pin = -1;
    HAL_GPIO_WritePin_GPIOx = -1;
    HAL_GPIO_WritePin_GPIO_Pin = -1;
    HAL_GPIO_WritePin_PinState = GPIO_PIN_RESET;
    HAL_GPIO_ReadPin_return = GPIO_PIN_RESET;
}


uint32_t Mock_HAL_GPIO::HAL_GetTick(void) {
    HAL_GetTick_counter++;
    return HAL_GetTick_counter * READING_RATE/5;
}

GPIO_PinState Mock_HAL_GPIO::HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    HAL_GPIO_ReadPin_GPIOx = *GPIOx;
    HAL_GPIO_ReadPin_GPIO_Pin = GPIO_Pin;
    HAL_GPIO_ReadPin_return = HAL_GPIO_ReadPin_return == GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET;
    return HAL_GPIO_ReadPin_return;
}

void Mock_HAL_GPIO::HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
    uintptr_t GPIOx_int = (uintptr_t)GPIOx;
    HAL_GPIO_WritePin_GPIOx = GPIOx_int;
    HAL_GPIO_WritePin_GPIO_Pin = GPIO_Pin;
    HAL_GPIO_WritePin_PinState = PinState;
}