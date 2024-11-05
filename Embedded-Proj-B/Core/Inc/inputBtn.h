/*
 * inputBtn.h
 *
 *  Created on: Oct 16, 2024
 *      Author: color
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#ifndef INC_INPUTBTN_H_
#define INC_INPUTBTN_H_

class inputBtn { // @suppress("Miss copy constructor or assignment operator")
	private:
    uint8_t cstate = 0;
    uint8_t pstate = 0;
    int8_t msg = 0;
public:
    uint32_t pinNum;
    GPIO_TypeDef* gpio_address;
    //Functions
    inputBtn(GPIO_TypeDef* , uint32_t);
    int8_t stateMachine();
};

#endif /* SRC_INPUTBTN_H_ */
