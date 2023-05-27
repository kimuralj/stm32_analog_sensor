#include <cstdio>
#include <gtest/gtest.h>
#include <cmath>
#include "tests.h"


TEST(PotSensor, UsingSameHandler) {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
    ADC_HandleTypeDef hadc[3] = {1,2,3};

    for(auto handler:hadc) {
        PotSensor__Initialize(&handler);
        (void) PotSensor__GetResistanceValue();
        ASSERT_EQ(Mock_HAL_ADC::HAL_ADC_Start_hadc, handler);
        ASSERT_EQ(Mock_HAL_ADC::HAL_ADC_PollForConversion_hadc, handler);
        ASSERT_EQ(Mock_HAL_ADC::HAL_ADC_GetValue_hadc, handler);
    }
}

TEST(PotSensor, GetRightResistanceValue) {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
    ADC_HandleTypeDef hadc1 = 1;
    PotSensor__Initialize(&hadc1);
    
    float pot_value = PotSensor__GetResistanceValue();

    float resistence_value = (float)HAL_ADC_GetValue(&hadc1) * 10 / 4095;
    
    ASSERT_GE(pot_value, 0);
    ASSERT_LE(pot_value, 10);

    ASSERT_FLOAT_EQ(pot_value, resistence_value);
}

TEST(PotSensor, GetRightResistanceEveryADC) {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
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

TEST(Communication, UsingSameHandler) {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
    UART_HandleTypeDef huart[3] = {1,2,3};
    uint8_t buffer[BUFFER_SIZE];

    for(auto handler:huart) {
        Communication__Initialize(&handler);
        Communication__SendNewMessage(1.0);
        Communication__ReceiveNewMessage(buffer);
        ASSERT_EQ(Mock_HAL_UART::HAL_UART_Transmit_huart, handler);
        ASSERT_EQ(Mock_HAL_UART::HAL_UART_Receive_IT_huart, handler);
    }
}

TEST(Communication, SendNewMessageFloatRange) {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
    UART_HandleTypeDef huart = 1;
    uint8_t byte_ptr[BUFFER_SIZE] = {0};

    const int dec = 2;
    const float step = pow(10,-dec);
    const float mult_round = pow(10,dec);

    Communication__Initialize(&huart);
    for(float i = 0; 10 - i >= 0; i += step) {
        i = round(i*mult_round) / mult_round;
        if(i > 10.0) i = 10.0;
        Communication__SendNewMessage(i);
        ASSERT_EQ(Mock_HAL_UART::HAL_UART_Transmit_huart, huart);
        printf("float input:%.2f ",i);
        // printf("payload:",i); for(auto j = 0; j < BUFFER_SIZE; j++) printf("%d ",Mock_HAL_UART::HAL_UART_Transmit_pData[j]);
        for(auto j = 0; j < 4; j++) {
            byte_ptr[j] = Mock_HAL_UART::HAL_UART_Transmit_pData[4-j];
        }
        // printf("byte_ptr: "); for(auto j = 0; j < 4; j++) printf("%d ",byte_ptr[j]);
        float output = *(float*)byte_ptr;
        printf("float output:%.2f\n",output);
        ASSERT_FLOAT_EQ(i, output);
    }
}
