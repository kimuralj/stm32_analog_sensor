#include "tests.h"
#include <gtest/gtest.h>

TEST(PotSensor, ReadFromRightHandler) {
    ADC_HandleTypeDef hadc[3] = {1,2,3};

    for(auto handler:hadc) {
        PotSensor__Initialize(&handler);
        (void) PotSensor__GetResistanceValue();
        ASSERT_EQ(HALMock::HAL_ADC_Start_hadc, handler);
        ASSERT_EQ(HALMock::HAL_ADC_PollForConversion_hadc, handler);
        ASSERT_EQ(HALMock::HAL_ADC_GetValue_hadc, handler);
    }
}

TEST(PotSensor, GetRightResistanceValue) {
    ADC_HandleTypeDef hadc1 = 1;
    PotSensor__Initialize(&hadc1);
    
    float pot_value = PotSensor__GetResistanceValue();

    float resistence_value = (float)HAL_ADC_GetValue(&hadc1) * 10 / 4095;
    
    ASSERT_GE(pot_value, 0);
    ASSERT_LE(pot_value, 10);

    ASSERT_FLOAT_EQ(pot_value, resistence_value);
}

TEST(PotSensor, GetRightResistanceEveryADC) {
    ADC_HandleTypeDef hadc[3] = {1,2,3};
    for(auto handler:hadc) {
        PotSensor__Initialize(&handler);
        
        float pot_value = PotSensor__GetResistanceValue();

        float resistence_value = (float)HAL_ADC_GetValue(&handler) * 10 / 4095;
        
        ASSERT_GE(pot_value, 0);
        ASSERT_LE(pot_value, 10);

        ASSERT_FLOAT_EQ(pot_value, resistence_value);
    }
}
