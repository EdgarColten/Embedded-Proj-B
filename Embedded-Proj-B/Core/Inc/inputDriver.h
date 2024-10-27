/*
 * inputDriver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: color
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
    uint8_t peState;
public:
    GPIO_TypeDef* gpio_addressA;
    GPIO_TypeDef* gpio_addressB;
    //nextState* queue; this will be fixed once we add struct
    int8_t pinNumA;
    int8_t pinNumB;
    //Functions
    inputDriver(GPIO_TypeDef* , GPIO_TypeDef* ,uint8_t,uint8_t);
    uint32_t edgeDetector();
};

#endif /* INPUTDRIVER_H_ */
