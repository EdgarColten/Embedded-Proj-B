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
#include "cpp_main.h"

#ifndef INC_OUTPUTDRIVER_H_
#define INC_OUTPUTDRIVER_H_

#define PI 3.1415926535
#define MAX_SIZE 4096
#define SIZE 256
#define CPU_CLK 70000000

class OutputDriver{ // @suppress("Miss copy constructor or assignment operator")
private:
	Queue* queue;
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
	uint32_t sineWave[SIZE];
	uint32_t squareWave[SIZE];
	uint32_t pulseWave[SIZE];
	uint32_t delayWave[SIZE];

	enum waveType shape; //delay is only for channel 2

public:
	OutputDriver(uint8_t);
	void update();
	void update_Channel(uint32_t, uint32_t,wave);
	void generateSquare();
	void generateSine();
	void generatePulse();
	void generateDelay(OutputDriver,uint32_t);
	uint32_t getWave(OutputDriver);
	void setShape(wave);
};

#endif /* INC_OUTPUTDRIVER_H_ */
