/*
 * inputDriver.h
 *
 *  Created on: Oct 8, 2024
 *      Author: color
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#ifndef INPUTDRIVER_H_
#define INPUTDRIVER_H_
//just doing this for git testing purposes 2
class inputDriver { // @suppress("Miss copy constructor or assignment operator")
private:
    uint8_t cState;
    uint8_t pState;
    uint8_t eState;
    uint8_t peState;
public:
    GPIO_TypeDef* gpio_addressA;
    GPIO_TypeDef* gpio_addressB;
    //nextState* queue; this will be fixed once we add struct
    int8_t message;
    int8_t pinNumA;
    int8_t pinNumB;
    //Functions
    inputDriver(GPIO_TypeDef* , GPIO_TypeDef* ,uint8_t,uint8_t,int8_t);
    void stateMachine();
    void edgeDetector();


};

#endif /* INPUTDRIVER_H_ */
