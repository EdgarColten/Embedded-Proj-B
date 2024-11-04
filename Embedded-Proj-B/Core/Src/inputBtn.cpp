/*
 * inputBtn.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: color
 */

#include "inputBtn.h"
#include "stm32l4xx_hal.h"
#include <cstdint>

inputBtn::inputBtn(GPIO_TypeDef* gpioAddress, uint32_t pinN) {
	 gpio_address = gpioAddress;
	 pinNum = pinN;
}
int8_t inputBtn::stateMachine(){
    if ((gpio_address -> IDR & (1<<pinNum)) == 0)
    {
    	cstate = 1;

    }
    else
    {
    	cstate = 0;

    }
    if(cstate && !pstate){
    	msg = 1;
    }
    else
    {
    	msg = 0;
    }
    pstate = cstate;
    return msg;
}
