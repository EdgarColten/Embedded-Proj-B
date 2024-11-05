/*
 *  Created on: Oct 16, 2024
 *      Author: color
 */

/**
 * @file  inputBtn.h
 * @brief Input Driver designed for a button
 *
 *
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
    inputBtn(GPIO_TypeDef* , uint32_t); //Constructor

    int8_t stateMachine();
    /**
     * @brief this function checks the current state of an input pin and compares it to the previous state to determine if the button has been pressed.
     * It firsts checks for a low edge (given a pull-up resistor) and then checks to see if it differs from the previous state, if yes then button has been pressed.
     * @return 1 if the button has been pressed, 0 if it has not
     */
};

#endif /* SRC_INPUTBTN_H_ */
