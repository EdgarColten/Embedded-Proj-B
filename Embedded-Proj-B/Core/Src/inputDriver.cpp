/*
 * inputDriver.cpp
 *
 *  Created on: Oct 8, 2024
 *      Author: color
 */

#include "inputDriver.h"
#include "stm32l4xx_hal.h"
#include <cstdint>
//just doing this for git testing purposes 24
    inputDriver::inputDriver(GPIO_TypeDef* gpioA,GPIO_TypeDef* gpioB, uint8_t pNum, uint8_t pNum2)
    {
        gpio_addressA = gpioA;
        gpio_addressB = gpioB;
        pinNumA = pNum;
        pinNumB = pNum2;
        peState = 0;
        cState = 0;
    }
    uint32_t inputDriver::edgeDetector()
    {
        if(((gpio_addressA -> IDR & (1<<pinNumA)) == 0 && (gpio_addressB -> IDR & (1<<pinNumB)) == 0 )&& peState == 0){
            peState = 1;//pestate = 1 if A&B & not pestate
        }
        if(peState == 1)
        {
			if((gpio_addressA -> IDR & (1<<pinNumA)) == 0 && (gpio_addressB -> IDR & (1<<pinNumB)) == 1){
				cState = 2; //decrement, value can change, if pestate & turned left
				peState = 0;
				return cState;
			}else if((gpio_addressA -> IDR & (1<<pinNumA)) == 1 && (gpio_addressB -> IDR & (1<<pinNumB)) == 0)
			{
				cState = 1; //increment, value can change, if pestate & turned right
				peState = 0;
			}else
			{
				cState = 0; //Nothing
			}
        }else
        {
            cState = 0; //Returns 0 if !pestate
        }
        return cState;
    }
