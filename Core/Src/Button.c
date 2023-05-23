#include "Button.h"

static GPIO_TypeDef* Port;
static uint16_t Pin;
static uint32_t Previous_Time;

static GPIO_PinState Previous_Button_State;

void Button__Initialize(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	Previous_Time = HAL_GetTick();
	Previous_Button_State = GPIO_PIN_RESET;
	Port = GPIOx;
	Pin = GPIO_Pin;
}

uint8_t Button__GetTransitionEvent(void)
{
	uint8_t ret_val = 0;

	GPIO_PinState button_state = Previous_Button_State;
	uint32_t current_time;

    current_time = HAL_GetTick();
    if ( (current_time - Previous_Time) > READING_RATE)
    {
    	button_state = HAL_GPIO_ReadPin(Port, Pin);
    	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, button_state);
		Previous_Time = current_time;
    }

    if(button_state == GPIO_PIN_SET && Previous_Button_State == GPIO_PIN_RESET)
    {
    	button_state = Previous_Button_State;
    	ret_val = 1;
    }

    return ret_val;
}
