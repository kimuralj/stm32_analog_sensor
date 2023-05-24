#include "Communication.h"
#include "string.h"

static UART_HandleTypeDef * myUart;

void Communication__Initialize(UART_HandleTypeDef *huart)
{
	myUart = huart;
}

void Communication__SendNewMessage(float value)
{
	uint8_t payload[BUFFER_SIZE];

	uint8_t * byte_ptr = (uint8_t *) &value;

	memset(&payload, 0, sizeof(payload));

	payload[0] = 5;
	payload[1] = byte_ptr[3];
	payload[2] = byte_ptr[2];
	payload[3] = byte_ptr[1];
	payload[4] = byte_ptr[0];

	HAL_UART_Transmit(myUart, payload, sizeof(payload), 100);
}

void Communication__ReceiveNewMessage(uint8_t *buffer)
{
	memset(buffer, 0, sizeof(*buffer));
	HAL_UART_Receive_IT(myUart, buffer, BUFFER_SIZE);
}
