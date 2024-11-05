/*
 * inputSlide.h
 *
 *  Created on: Oct 29, 2024
 *      Author: color
 */

#ifndef INC_INPUTSLIDE_H_
#define INC_INPUTSLIDE_H_
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
class inputSlide { // @suppress("Miss copy constructor or assignment operator")
public:
	uint32_t pinNum;
    GPIO_TypeDef* gpio_address;
    uint8_t rValue;
	inputSlide(GPIO_TypeDef*,uint32_t);
	int8_t slideGet();

};

#endif /* INC_INPUTSLIDE_H_ */
