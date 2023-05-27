#include <cstdio>
#include <gtest/gtest.h>
#include <cmath>
#include "tests.h"

void reset_all() {
    Mock_HAL_ADC::reset();
    Mock_HAL_UART::reset();
    Mock_HAL_GPIO::reset();
}

TEST(PotSensor, UsingSameHandler) {
    reset_all();
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
    reset_all();
    ADC_HandleTypeDef hadc1 = 1;
    PotSensor__Initialize(&hadc1);
    
    float pot_value = PotSensor__GetResistanceValue();

    float resistence_value = (float)HAL_ADC_GetValue(&hadc1) * 10 / 4095;
    
    ASSERT_GE(pot_value, 0);
    ASSERT_LE(pot_value, 10);

    ASSERT_FLOAT_EQ(pot_value, resistence_value);
}

TEST(PotSensor, GetRightResistanceEveryADC) {
    reset_all();
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
    reset_all();
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
    reset_all();
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
        for(auto j = 0; j < 4; j++) {
            byte_ptr[j] = Mock_HAL_UART::HAL_UART_Transmit_pData[4-j];
        }
        float output = *(float*)byte_ptr;
        ASSERT_FLOAT_EQ(i, output);
    }
}

TEST(Communication, ReceiveNewMessageEmpty) {
    reset_all();
    UART_HandleTypeDef huart = 1;
    uint8_t buffer[BUFFER_SIZE] = {0};
    uint8_t byte_ptr[BUFFER_SIZE] = {0};
    Communication__Initialize(&huart);
    Communication__ReceiveNewMessage(buffer);
    ASSERT_EQ(Mock_HAL_UART::HAL_UART_Receive_IT_huart, huart);
    for(auto j = 0; j < BUFFER_SIZE; j++) {
        ASSERT_EQ(buffer[j], UINT8_MAX);
    }
}

TEST(Communication, SendAndReceiveNewMessage) {
    reset_all();
    UART_HandleTypeDef huart = 1;
    uint8_t buffer[BUFFER_SIZE] = {0};
    uint8_t byte_ptr[BUFFER_SIZE] = {0};

    const int dec = 2;
    const float step = pow(10,-dec);
    const float mult_round = pow(10,dec);

    Communication__Initialize(&huart);
    for(float i = 0; 10 - i >= 0; i += step) {
        i = round(i*mult_round) / mult_round;
        if(i > 10.0) i = 10.0;
        Communication__SendNewMessage(i);
        Communication__ReceiveNewMessage(buffer);
        ASSERT_EQ(Mock_HAL_UART::HAL_UART_Transmit_huart, huart);
        for(auto j = 0; j < BUFFER_SIZE; j++) {
            ASSERT_EQ(Mock_HAL_UART::HAL_UART_Transmit_pData[j], buffer[j]);
        }
    }
}

TEST(Button, UsingSamePortAndPin) {
    reset_all();
    GPIO_TypeDef GPIOx[3] = {1,2,3};
    uint16_t GPIO_Pin[3] = {1,2,3};

    for(auto port:GPIOx) {
        for(auto pin:GPIO_Pin) {
            reset_all();
            Button__Initialize(&port, pin);
            for(auto i = 0; i < 5; i++) {
                (void) Button__GetTransitionEvent();
            }
            // next get transition event will be called
            (void) Button__GetTransitionEvent();
            ASSERT_EQ(Mock_HAL_GPIO::HAL_GPIO_ReadPin_GPIOx, port);
            ASSERT_EQ(Mock_HAL_GPIO::HAL_GPIO_ReadPin_GPIO_Pin, pin);
        }
    }
}

TEST(Button, TriggerTransitionEventWriteOnRightTime) {
    reset_all();
    GPIO_TypeDef GPIOx = 2;
    uint16_t GPIO_Pin = 3;
    uint8_t getTransitionEventReturn;

    GPIO_TypeDef GPIO_port_write_begin = Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIOx;
    uint16_t GPIO_pin_write_begin = Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIO_Pin;

    Button__Initialize(&GPIOx, GPIO_Pin);
    for(auto i = 0; i < 5; i++) {
        getTransitionEventReturn = Button__GetTransitionEvent();
        ASSERT_EQ(GPIO_port_write_begin, Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIOx);
    }
    // next get transition event will be called
    getTransitionEventReturn = Button__GetTransitionEvent();
    ASSERT_NE(GPIO_port_write_begin, Mock_HAL_GPIO::HAL_GPIO_WritePin_GPIOx);
}

TEST(Button, TriggerTransitionEventReturnCorrectly) {
    reset_all();
    GPIO_TypeDef GPIOx = 2;
    uint16_t GPIO_Pin = 3;
    uint8_t getTransitionEventReturn;

    Button__Initialize(&GPIOx, GPIO_Pin);
    for(auto i = 0; i < 5; i++) {
        getTransitionEventReturn = Button__GetTransitionEvent();
        ASSERT_EQ(getTransitionEventReturn, 0);
    }
    // next get transition event will be called
    getTransitionEventReturn = Button__GetTransitionEvent();
    ASSERT_EQ(getTransitionEventReturn, 1);

    for(auto i = 0; i < 5; i++) {
        getTransitionEventReturn = Button__GetTransitionEvent();
        ASSERT_EQ(getTransitionEventReturn, 0);
    }
    // next get transition event will be called
    getTransitionEventReturn = Button__GetTransitionEvent();
    ASSERT_EQ(getTransitionEventReturn, 0);

    for(auto i = 0; i < 5; i++) {
        getTransitionEventReturn = Button__GetTransitionEvent();
        ASSERT_EQ(getTransitionEventReturn, 0);
    }
    // next get transition event will be called
    getTransitionEventReturn = Button__GetTransitionEvent();
    ASSERT_EQ(getTransitionEventReturn, 1);
}