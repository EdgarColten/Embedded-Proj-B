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

//uint32_t DAC_OUT_FREQ_VALUES[] = {};

class OutputDriver{
private:
	Queue* queue;
	uint32_t freq;
	uint32_t amp;
	uint32_t autoReload;
	enum shape {sine,square,pulse,delay}shape; //delay is only for channel 2

public:
	OutputDriver();
	void update();
	void update_Channel1(uint32_t, uint32_t);
	void update_Channel2();
	void generateSquare(uint32_t*,uint16_t);
	void generateSine(uint32_t*,uint16_t);

};



#endif /* INC_OUTPUTDRIVER_H_ */
