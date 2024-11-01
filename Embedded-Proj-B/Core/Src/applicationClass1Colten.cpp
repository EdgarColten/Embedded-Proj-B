/*
 * main_cpp_Colten.cpp
 *
 *  Created on: Sep 27, 2024
 *      Author: credgar21
 */

#include <cstdint>

//Custom headers
#include "cpp_main.h"
#include "Queue.h"
#include "channel.h"

extern "C" void cpp_main(void);

/*
Test Cases
myChannel1->setFreq(1);
myChannel1->setFreq(1);
myChannel1->setFreq(1);

myChannel1->setAmp(1);
myChannel1->setAmp(-1);

myChannel1->setDelay(-1);
myChannel1->setDelay(-1);
myChannel1->setDelay(-1);
*/

//*	Colten Demonstrated JPL RULES
/*

Level 2:
	Rule 3: Use verifiable loop bounds for all loops meant to be terminating.
	Rule 5: Do not use dynamic memory allocation after task initialization.
	Rule 9: Place restrictions on the use of semaphores and locks.
	Rule 11: Do not use goto, setjmp, or longjmp

Level 3:
	Rule 17: Use U32, I16, etc instead of predefined C data types such as int, short, etc.
	Rule 18: Make the order of evaluation in compound expressions explicit.
	Rule 19: Do not use expressions with side effects.


*/

Channel::Channel(inputQueue* iQ, waveQueue* wQ) // @suppress("Class members should be properly initialized")
{
	shapeCount = 0;
	freqCount = 0;
	ampCount = 0;
	delayCount = 0;
	chanCount = 1;
	Input_q = iQ;
	Wave_q = wQ;
}

void Channel::setWaveType(int8_t val){
		if(shapeCount < 3 && val > 0){
			shapeCount = shapeCount + 1;
		}
		else if(shapeCount == 3 && val > 0)
		{
			shapeCount = 0;
		}

		switch(shapeCount){

		case 0:
			myWaveProp.type = sine;
			break;

		case 1:
			myWaveProp.type = square;
			break;


		case 2:
			myWaveProp.type = pulse;
			break;

		case 3:
			myWaveProp.type = delay;
			break;
		default:
			break;
		return;
		}
	}

void Channel::setFreq(int8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		if(freqCount < 20 && val > 0){
			freqCount = freqCount + 1;
		}
		else if(freqCount > 0 && val < 0){
			freqCount = freqCount - 1;
		}

		if(freqCount == 0){
			myWaveProp.frequency = 1;
		}
		else{
			myWaveProp.frequency = 50*freqCount;
		}
			return;

	}

void Channel::setAmp(int8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		if(ampCount < 33 && val > 0){
			ampCount = ampCount + 1;
		}
		else if(ampCount > 0 && val < 0){
			ampCount = ampCount + -1;
		}
		//Example of Rule 18 (Including () to ensure correct computation in correct order)
		myWaveProp.amplitude = ((ampCount * 0.1) + 0.1) * 1240;
		return;
	}

void Channel::setDelay(int8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		if(val>0 && delayCount<7){
			delayCount = delayCount + 1;
	}
		else if(val<0 && delayCount>0){
			delayCount = delayCount - 1;
		}

		myWaveProp.delay = delayCount;
		return;
	}

void Channel::updateChannel(){
	nextState ns;
	Input_q->dequeue(&ns);
	setFreq(ns.knobF);
	setAmp(ns.knobA);
	setDelay(ns.knobD);
	setWaveType(ns.btn_S);
	myWaveProp.channel = ns.sw_select;
	Wave_q->enqueue(myWaveProp);
}

/*
void Channel::cpChannel(waveProp x){ //x is ch1 so the delay value should be 0. This may not give the correct delay
		myWaveProp.type = x.type;
		myWaveProp.frequency = x.frequency;
		myWaveProp.amplitude = x.amplitude;
		myWaveProp.delay = x.delay;
		return;
}
*/



