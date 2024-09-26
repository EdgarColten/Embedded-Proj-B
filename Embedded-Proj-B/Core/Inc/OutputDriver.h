/*
 * OutputDriver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "Queue.h"

#ifndef INC_OUTPUTDRIVER_H_
#define INC_OUTPUTDRIVER_H_

extern uint32_t DAC_OUT_SINE_STEP_VALUES[24];
//uint32_t DAC_OUT_FREQ_VALUES[] = {};

class OutputDriver{
private:
	Queue* queue;
	uint32_t freq;
	uint32_t amp;
	enum shape {sine,square,pulse,delay}shape; //delay is only for channel 2

public:
	OutputDriver();
	void update();
	void update_Channel1();
	void update_Channel2();

};



#endif /* INC_OUTPUTDRIVER_H_ */
