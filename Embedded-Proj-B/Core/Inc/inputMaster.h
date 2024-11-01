/*
 * inputMaster.h
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "cpp_main.h"
#ifndef INC_INPUTMASTER_H_
#define INC_INPUTMASTER_H_
class inputMaster { //This class is the master input driver which takes 4 inputs and puts them into a struct to send to Q//
public:
	inputMaster();
	nextState nState;
	nextState masterGet(int8_t,int8_t,int8_t,int8_t, int8_t);
};

#endif /* SRC_INPUTMASTER_H_ */
