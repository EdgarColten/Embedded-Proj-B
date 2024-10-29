/*
 * inputSlide.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: color
 */

#include "inputSlide.h"
#include "stm32l4xx_hal.h"
#include <cstdint>
inputSlide::inputSlide(GPIO_TypeDef* gpioAddress, uint8_t pinN) {
	gpio_address = gpioAddress;
	pinNum = pinN;
	rValue = (gpio_address -> IDR & (1<<pinNum));
}
uint8_t inputSlide::slideGet(){
	rValue = (gpio_address -> IDR & (1<<pinNum));
	return rValue;
}
