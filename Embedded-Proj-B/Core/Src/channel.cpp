/*
 * main_cpp_Colten.cpp
 *
 *  Created on: Sep 27, 2024
 *      Author: credgar21
 */

#include <cstdint>
#include <cassert>

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
	Rule 3: Use verifiable loop bounds for all loops meant to be terminating.		All Loops have a predetermined unchangable bound except for while 1 loop in cpp main and in main
	Rule 5: Do not use dynamic memory allocation after task initialization.			Checked for malloc throughout code and never used
	Rule 9: Place restrictions on the use of semaphores and locks.					Semaphore has defined bounds. (Size of 2)
	Rule 11: Do not use goto, setjmp, or longjmp									Checked for goto, setjmp, and longjmp in code and never used

Level 3:
	Rule 17: Use U32, I16, etc instead of predefined C data types such as int, short, etc.			All variables are of type U32 or the like except in syscalls.c, does not break rule
	Rule 18: Make the order of evaluation in compound expressions explicit.							All complex equations used have explicit parenthesis used to separates the operations in the correct order.
	Rule 19: Do not use expressions with side effects.												Checking if statements to ensure values are never set to variable instead of checked. All variables are assigned values not changing the values of the given variable unless specified/intentional


*/

Channel::Channel(inputQueue* iQ, waveQueue* wQ) // @suppress("Class members should be properly initialized")
{
	//default values for waves
	myWaveProp.frequency1 = 100;
	myWaveProp.amplitude1 = 2045;
	myWaveProp.type1 = sine;

	myWaveProp.amplitude2 = 2045;
	myWaveProp.frequency2 = 100;
	myWaveProp.type2 = sine;

	myWaveProp.delay = 0;
	myWaveProp.channel = 1;

	shapeCount1 = 0;
	freqCount1 = 3;
	ampCount1 = 15;

	shapeCount2 = 0;
	freqCount2 = 3;
	ampCount2 = 15;

	delayCount = 0;

	assert(delayCount == 0);
	chanCount = 1;
	Input_q = iQ;
	Wave_q = wQ;
}

void Channel::setWaveType(){

	if(ns.btn_S == 0)
		return;
	assert(ns.btn_S != 0);

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

	else if((ns.btn_S == 1) && (chanCount == 2)){
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

	if(ns.knobF == 0)
		return;
	assert(ns.knobF != 0);

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

		if(ns.knobA == 0)
			return;
		assert(ns.knobA != 0);
		if(chanCount == 1)
		{
			if(ampCount1 < 31 && ns.knobA == 1){
				ampCount1 = ampCount1 + 1;
			}

			else if(ampCount1 > 1 && ns.knobA == -1){
				ampCount1 = ampCount1 + -1;
			}

			else if(ampCount1 == 31 && ns.knobA == 1){
				ampCount1 = 31;
			}

			else if(ampCount1 == 0 && ns.knobA == -1){
				ampCount1 = 1;
			}

			myWaveProp.amplitude1 = ((ampCount1 * 0.1) + 0.1) * 1260;
			return;
		}

		if(chanCount == 2)
		{
			if(ampCount2 < 31 && ns.knobA == 1){
				ampCount2 = ampCount2 + 1;
			}

			else if(ampCount2 > 1 && ns.knobA == -1){
				ampCount2 = ampCount2 + -1;
			}

			else if(ampCount2 == 31 && ns.knobA == 1){
				ampCount2 = 31;
			}

			else if(ampCount2 == 1 && ns.knobA == -1){
				ampCount2 = 1;
			}

			myWaveProp.amplitude2 = ((ampCount2 * 0.1) + 0.1) * 1260;
			return;
		}


}

void Channel::setDelay(){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
	if(chanCount == 2)
	{
		if(ns.knobD == 0)
			return;
		assert(ns.knobD != 0);

		if(delayCount < 7 && ns.knobD == 1){
			delayCount = delayCount + 1;
			myWaveProp.delay = delayCount;
			return;
		}

		else if(delayCount > 0 && ns.knobD == -1 ){
			delayCount = delayCount - 1;
			myWaveProp.delay = delayCount;
			return;
		}

		else if(delayCount == 7 && ns.knobD == 1){
			delayCount = 7;
			myWaveProp.delay = delayCount;
			return;
		}

		else if(delayCount == 0 && ns.knobD == -1 ){
			delayCount = 0;
			myWaveProp.delay = delayCount;
			return;
		}

	}


}


void Channel::updateChannel(){

	bool notEmpty = Input_q->dequeue(&ns);

	if(notEmpty == false)
	{
		Wave_q->enqueue(myWaveProp);
		return;
	}


	chanCount = ns.sw_select;

	assert(chanCount == ns.sw_select);

	setFreq();
	setAmp();
	setDelay();
	setWaveType();
	myWaveProp.channel = chanCount;


	Wave_q->enqueue(myWaveProp);
}





