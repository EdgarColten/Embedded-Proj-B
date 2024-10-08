/*
 * OutputDriver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

//Custom includes
#include "Queue.h"
#include "cpp_main.h"

#ifndef INC_OUTPUTDRIVER_H_
#define INC_OUTPUTDRIVER_H_

#define PI 3.1415926535
#define MAX_SIZE 4096
#define SIZE 256
#define CPU_CLK 80000000

class OutputDriver{ // @suppress("Miss copy constructor or assignment operator")
private:

	Queue* queue;

	//Core attributes
	uint32_t freq;
	uint32_t amp;
	uint32_t autoReload;
	uint8_t channel;

	//Generation checks
	bool updateSine;
	bool updateSquare;
	bool updatePulse;
	bool updateDelay;

	//Output wave tables
	uint32_t outWave[SIZE];

	//Setting wave type
	enum waveType shape; //delay is only for channel 2

public:
	OutputDriver(uint8_t);
	void update_Channel(waveProp,OutputDriver);
	void calculateAutoReload(uint32_t);

	void setAttributes(waveProp);
	void getAttributes(waveProp*);
	void generateWave();
	wave getShape();
	uint32_t getAmp();
	uint32_t getFreq();
	void setAutoReload(TIM_HandleTypeDef*);
};

#endif /* INC_OUTPUTDRIVER_H_ */
