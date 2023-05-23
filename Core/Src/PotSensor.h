#ifndef _POTSENSOR_
#define _POTSENSOR_

#include "main.h"

void PotSensor__Initialize(ADC_HandleTypeDef* adc_var);
float PotSensor__GetResistanceValue(void);

#endif
