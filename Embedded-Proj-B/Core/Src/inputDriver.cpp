/*
 * inputDriver.cpp
 *
 *  Created on: Oct 8, 2024
 *      Author: color
 */

#include "inputDriver.h"
#include "stm32l4xx_hal.h"
#include <cstdint>

    inputDriver::inputDriver(GPIO_TypeDef* gpioA,GPIO_TypeDef* gpioB, uint8_t pNum, uint8_t pNum2, int8_t msg)
    {
        gpio_addressA = gpioA;
        gpio_addressB = gpioB;
        message = msg;
        pinNumA = pNum;
        pinNumB = pNum2;
    }
    void inputDriver::stateMachine()
    {

    }
    void inputDriver::edgeDetector()
    {
        if(((gpio_addressA -> IDR & (1<<pinNumA)) == 0 && (gpio_addressB -> IDR & (1<<pinNumB)) == 0 )&& peState == 0){
            peState = 1;
        }
        if(peState == 1)
        {
        if((gpio_addressA -> IDR & (1<<pinNumA)) == 0 && (gpio_addressB -> IDR & (1<<pinNumB) == 1)){
            cState = 2; //decrement
            peState = 0;
        }else if((gpio_addressB -> IDR & (1<<pinNumB)) == 0 && (gpio_addressB -> IDR & (1<<pinNumB) == 1))
        {
            cState = 1; //increment
            peState = 0;
        }else
        {
            cState = 0;
        }
        }else
        {
            cState = 0;
        }
    }
