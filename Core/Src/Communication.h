#ifndef _COMMUNICATION_
#define _COMMUNICATION_

#include "main.h"

#define BUFFER_SIZE		13

void Communication__Initialize(UART_HandleTypeDef *huart);
void Communication__SendNewMessage(float value);
HAL_UART_StateTypeDef Communication__GetState(void);
void Communication__ReceiveNewMessage(uint8_t *buffer);

#endif
