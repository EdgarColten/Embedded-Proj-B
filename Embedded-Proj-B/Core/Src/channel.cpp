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
	//default values for waves
	myWaveProp.frequency1 = 1;
	myWaveProp.amplitude1 = 124;
	myWaveProp.type1 = sine;

	myWaveProp.amplitude2 = 124;
	myWaveProp.frequency2 = 1;
	myWaveProp.type2 = sine;

	myWaveProp.delay = 0;
	myWaveProp.channel = 1;

	shapeCount1 = 0;
	freqCount1 = 0;
	ampCount1 = 0;

	shapeCount2 = 0;
	freqCount2 = 0;
	ampCount2 = 0;

	delayCount = 0;
	chanCount = 1;
	Input_q = iQ;
	Wave_q = wQ;
}

void Channel::setWaveType(){

	if(ns.btn_S == 1 && chanCount == 1){
		if(shapeCount1 < 2){
			shapeCount1 = shapeCount1 + 1;
		}
		else
		{
			shapeCount1 = 0;
		}

		switch(shapeCount1){

		case 0:
			myWaveProp.type1 = sine;
			break;

		case 1:
			myWaveProp.type1 = square;
			break;


		case 2:
			myWaveProp.type1 = pulse;
			break;

		default:
			break;

		}
	}

	else if(ns.btn_S == 1 && chanCount == 2){
		if(shapeCount2 < 3){
			shapeCount2 = shapeCount2 + 1;
		}
		else
		{
			shapeCount2 = 0;
		}


		switch(shapeCount2){

		case 0:
			myWaveProp.type2 = sine;
			break;

		case 1:
			myWaveProp.type2 = square;
			break;


		case 2:
			myWaveProp.type2 = pulse;
			break;

		case 3:
			myWaveProp.type2 = delay;
			break;
		default:
			break;
		return;
		}

	}



	}

void Channel::setFreq(){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs


	if(chanCount == 1)
	{
		if(freqCount1 < 20 && ns.knobF == 1){
			freqCount1 = freqCount1 + 1;
		}
		else if(freqCount1 > 0 && ns.knobF == -1){
			freqCount1 = freqCount1 - 1;
		}

		else if(freqCount1 == 20 && ns.knobF == 1){ //when frequency is 1000 Hz and someone rotates knob cw
			freqCount1 = 20;
		}

		else if(freqCount1 == 0 && ns.knobF == -1){ //when frequency is 1 Hz and someone rotates knob ccw
			freqCount1 = 0;
		}

		if(freqCount1 == 0){
			myWaveProp.frequency1 = 1;
			return;
		}

		else{
			myWaveProp.frequency1 = 50*freqCount1;
			return;
		}
	}


	if(chanCount == 2)
	{
		if(freqCount2 < 20 && ns.knobF == 1){
			freqCount2 = freqCount2 + 1;
		}
		else if(freqCount2 > 0 && ns.knobF == -1){
			freqCount2 = freqCount2 - 1;
		}

		else if(freqCount2 == 20 && ns.knobF == 1){ //when frequency is 1000 Hz and someone rotates knob cw
			freqCount2 = 20;
		}

		else if(freqCount2 == 0 && ns.knobF == -1){ //when frequency is 1 Hz and someone rotates knob ccw
			freqCount2 = 0;
		}

		if(freqCount2 == 0){
			myWaveProp.frequency2 = 1;
			return;
		}

		else{
			myWaveProp.frequency2 = 50*freqCount2;
			return;
		}

	}



}

void Channel::setAmp(){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs

		if(chanCount == 1)
		{
			if(ampCount1 < 33 && ns.knobA == 1){
				ampCount1 = ampCount1 + 1;
			}

			else if(ampCount1 > 0 && ns.knobA == -1){
				ampCount1 = ampCount1 + -1;
			}

			else if(ampCount1 == 33 && ns.knobA == 1){
				ampCount1 = 33;
			}

			else if(ampCount1 == 0 && ns.knobA == -1){
				ampCount1 = 0;
			}

			myWaveProp.amplitude1 = ((ampCount1 * 0.1) + 0.1) * 1240;
			return;
		}

		if(chanCount == 2)
		{
			if(ampCount2 < 33 && ns.knobA == 1){
				ampCount2 = ampCount2 + 1;
			}

			else if(ampCount2 > 0 && ns.knobA == -1){
				ampCount2 = ampCount2 + -1;
			}

			else if(ampCount2 == 33 && ns.knobA == 1){
				ampCount2 = 33;
			}

			else if(ampCount2 == 0 && ns.knobA == -1){
				ampCount2 = 0;
			}

			myWaveProp.amplitude2 = ((ampCount2 * 0.1) + 0.1) * 1240;
			return;
		}


}

void Channel::setDelay(){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
	if(chanCount == 2)
	{
		if(ns.knobD == 1 && delayCount < 7){
			delayCount = delayCount + 1;
		}

		else if(ns.knobD == -1 && delayCount > 0){
			delayCount = delayCount - 1;
		}

		else if(ns.knobD == 1 && delayCount == 7){
			delayCount = 7;
		}

		else if(ns.knobD == -1 && delayCount == 0){
			delayCount = 0;
		}
		myWaveProp.delay = delayCount;
		return;
	}
	else
		return;
}


void Channel::updateChannel(){

	bool notEmpty = Input_q->dequeue(&ns);

	if(notEmpty == false)
	{
		Wave_q->enqueue(myWaveProp);
		return;
	}


	chanCount = ns.sw_select;

	setFreq();
	setAmp();
	setDelay();
	setWaveType();
	myWaveProp.channel = chanCount;


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



