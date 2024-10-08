/*
 * cpp_main.h
 *
 *  Created on: Sep 29, 2024
 *      Author: LogMa
 */

#ifndef INC_CPP_MAIN_H_
#define INC_CPP_MAIN_H_

//universal types needed in multiple files
typedef enum waveType {sine,square,pulse,delay}wave;

typedef struct{
	uint32_t frequency;
	uint32_t amplitude;
	uint32_t delay;
	wave type;
}waveProp;

typedef struct{
	int8_t knobF;
	int8_t knobA;
	int8_t knobD;
	int8_t btn;
}nextState;

#endif /* INC_CPP_MAIN_H_ */
