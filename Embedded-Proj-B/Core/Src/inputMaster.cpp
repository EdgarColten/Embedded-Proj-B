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
waveProp inputMaster::masterGet(uint32_t kF, uint32_t kA, uint32_t kD, wave kT){
	wProp.frequency = kF;
	wProp.amplitude = kA;
	wProp.delay = kD;
	wProp.type = kT;
	return wProp;
}
