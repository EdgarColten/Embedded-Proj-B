/*
 * inputDriver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: color
 */

/**
 * @file	inputDriver.h
 * @brief	Input driver designed for a quadrature knob
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#ifndef INC_INPUTDRIVER_H_
#define INC_INPUTDRIVER_H_
//just doing this for git testing purposes 24
class inputDriver { // @suppress("Miss copy constructor or assignment operator")
private:
    int8_t cState;
    uint32_t peState;
public:
    GPIO_TypeDef* gpio_addressA;
    GPIO_TypeDef* gpio_addressB;
    //nextState* queue; this will be fixed once we add struct
    uint32_t pinNumA;
    uint32_t pinNumB;
    //Functions
    inputDriver(GPIO_TypeDef* , GPIO_TypeDef* ,uint32_t,uint32_t);

    /**
     * @brief Checks value of user-chosen input pin and compares current state to previous state to determine whether the knob has been turned
     * First checks for pinA and pinB to both be low (given pull-up resistor) then checks for trailing edge to determine direction knob has been turned
     * @return Returns a 1 if pinA is the trailing edge, returns a -1 if pinB is trailing edge, returns a 0 if it has determined nothing has happened
     */
    int8_t edgeDetector();
};

#endif /* INPUTDRIVER_H_ */
