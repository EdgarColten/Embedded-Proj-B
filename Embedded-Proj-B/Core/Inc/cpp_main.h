/*
 * cpp_main.h
 *
 *  Created on: Sep 29, 2024
 *      Author: LogMa
 */
#include <cstdint>

#ifndef INC_CPP_MAIN_H_
#define INC_CPP_MAIN_H_

//universal types needed in multiple files
#define ONE_MS 80000
#define ONE_S 8000000

typedef enum waveType {sine,square,pulse,delay}wave;

typedef struct{
	uint32_t F;
	wave type;
	uint8_t channel;
	uint8_t offset;
} displayValues;

typedef struct{ //passed to the outputDriver for data collected by the input
	uint32_t frequency;
	uint32_t amplitude;
	uint32_t delay;
	wave type;
}waveProp;

typedef struct{
	int8_t knobF;
	int8_t knobA;
	int8_t knobD;
	int8_t knobS;
	int8_t btn;
}nextState;

#endif /* INC_CPP_MAIN_H_ */
