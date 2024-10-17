/*
 * inputMaster.h
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#ifndef INC_INPUTMASTER_H_
#define INC_INPUTMASTER_H_
	struct nextState{
		int8_t knobF;
		int8_t knobA;
		int8_t knobD;
		int8_t btn;
	};
class inputMaster { //This class is the master input driver which takes 4 inputs and puts them into a struct to send to Q//
public:

	inputMaster();
	nextState nState;
	nextState masterGet(int8_t,int8_t,int8_t,int8_t);

};

#endif /* SRC_INPUTMASTER_H_ */
