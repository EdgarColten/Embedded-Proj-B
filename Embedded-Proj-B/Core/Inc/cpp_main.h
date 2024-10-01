/*
 * cpp_main.h
 *
 *  Created on: Sep 29, 2024
 *      Author: LogMa
 */

#ifndef INC_CPP_MAIN_H_
#define INC_CPP_MAIN_H_

//universal variables needed in multiple files

typedef enum waveType {sine,square,pulse,delay}wave;

typedef struct{
	uint32_t frequency;
	uint32_t amplitude;
	uint32_t delay;
	wave type;
}waveProp;



#endif /* INC_CPP_MAIN_H_ */
