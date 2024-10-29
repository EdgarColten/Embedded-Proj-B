/*
 * inputMaster.cpp
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */

#include "inputMaster.h"
#include "stm32l4xx_hal.h"
#include <cstdint>
inputMaster::inputMaster() {
	// TODO Auto-generated constructor stub

}
nextState inputMaster::masterGet(int8_t kF, int8_t kA, int8_t kD, int8_t kS, int8_t kBtn){
	nState.knobF = kF;
	nState.knobA = kA;
	nState.knobD = kD;
	nState.knobS = kS;
	nState.btn = kBtn;
	return nState;
}
