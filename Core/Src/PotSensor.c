#include "PotSensor.h"

static ADC_HandleTypeDef* myAdcVar;

void PotSensor__Initialize(ADC_HandleTypeDef* adc_var)
{
	myAdcVar = adc_var;
}

float PotSensor__GetResistanceValue(void)
{
	float ret_val = 0;

	HAL_ADC_Start(myAdcVar);
	HAL_ADC_PollForConversion(myAdcVar, 100);
	ret_val = (float) HAL_ADC_GetValue(myAdcVar);

	ret_val = (10 * ret_val)/4095;

	return ret_val;
}
