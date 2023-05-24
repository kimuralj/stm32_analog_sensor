#ifndef _BUTTON_
#define _BUTTON_

#include "main.h"

#define READING_RATE	100
#define EVENT_CLICK		1

void Button__Initialize(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

uint8_t Button__GetTransitionEvent(void);

#endif
