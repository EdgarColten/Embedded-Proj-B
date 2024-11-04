/*
 * inputSlide.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: color
 */

#include "inputSlide.h"
#include "stm32l4xx_hal.h"
#include <cstdint>
inputSlide::inputSlide(GPIO_TypeDef* gpioAddress, uint32_t pinN) {
	gpio_address = gpioAddress;
	pinNum = pinN;
	rValue = 0;
}
int8_t inputSlide::slideGet(){
	if((gpio_address->IDR & (1<<pinNum)) == 0)
	{
		rValue = 1;

	}

	else
	{
		rValue = 0;

	}


	return rValue;
}
