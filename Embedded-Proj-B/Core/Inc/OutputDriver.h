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
#include "cpp_main.h"
#include "displayQueue.h"
#include "Queue.h"
#include "waveQueue.h"

#ifndef INC_OUTPUTDRIVER_H_
#define INC_OUTPUTDRIVER_H_

#define PI 3.1415926535
#define MAX_SIZE 4096
#define SIZE 256
#define CPU_CLK 80000000

#define PHASE_SHIFT 32 //value to shift the outWave buffer for the delay

class OutputDriver{ // @suppress("Miss copy constructor or assignment operator")
private:

	//IPC attributes
	displayQueue* oledQueue;
	waveQueue* signalQueue;


	//Core attributes
	uint32_t freq;
	uint32_t amp;
	uint32_t offset;
	uint32_t autoReload;
	uint8_t channel;


	//Output wave tables
	uint32_t outWave[SIZE];
	uint32_t sineWave[SIZE];
	uint32_t squareWave[SIZE];
	uint32_t pulseWave[SIZE];
	uint32_t delayOutWave[SIZE];

	//Setting wave type
	enum waveType shape; //delay is only for channel 2



	//packing values for the display
	displayValues dValues;


public:
	OutputDriver(uint8_t,waveQueue*,displayQueue*);
	void update_Channel(OutputDriver);
	void calculateAutoReload();

	void setAttributes(waveProp);
	void getAttributes(waveProp*);
	void generateWave();
	void setAutoReload(TIM_HandleTypeDef*);

	void delaySet();

	void pack();

};

#endif /* INC_OUTPUTDRIVER_H_ */
