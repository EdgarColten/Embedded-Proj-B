/*
 * inputMaster.cpp
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */

#include "inputMaster.h"
#include "stm32l4xx_hal.h"
#include <cstdint>
#include <cassert>
/*
David JPL Rules:
Level 2:
		4: Do not use task delays for task synchronization.								//Not using delays at all
		7: Do not use direct or indirect recursion										//No functions call themselves
		10 Use memory protection, safety margins, barrier patterns						//MemoryBuffer.h handles this for every Queue being used
		12: Do not use selective value assignments to elements of an enum list			//Using 1 enum that does not use selective value assignments
Level 3:
		13: Declare data objects at smallest possible level of scope					//Extern is used but it is used as advised by JPL
		14: Check the return value of non-void functions, or explicitly cast to (void)	//All return values are used in functions

*/
inputMaster::inputMaster(inputQueue* Ch, Semaphore* decide)
{
	channel = Ch;
	sem = decide;

	currentChannel = 1;
	freq = 0;
	amp = 0;
	delay = 0;
	shape = 0;

}


void inputMaster::update()
{
	uint32_t decision = 0;
	int8_t compareValue;
	bool notEmpty = sem->dequeue(&decision);

	if(notEmpty == false)
		return;

	if(decision != 1) //rush to return
		return;

	assert(decision == 1);
	//get current values from inputs

	compareValue = channel_Select.slideGet();

	if(compareValue == 0)
	{

		currentChannel = 1;

		freq = freq_knob.edgeDetector();
		amp = amp_knob.edgeDetector();
		shape = shape_btn.stateMachine();

		masterGet();
		channel->enqueue(nState);
		return;
	}

	else if(compareValue == 1)
	{

		currentChannel = 2;

		freq = freq_knob.edgeDetector();
		amp = amp_knob.edgeDetector();
		delay = delay_knob.edgeDetector();
		shape = shape_btn.stateMachine();

		masterGet();
		channel->enqueue(nState);
		return;
	}


}

void inputMaster::masterGet(){
	nState.knobF = freq;
	nState.knobA = amp;
	nState.knobD = delay;
	nState.btn_S = shape;
	nState.sw_select = currentChannel;
	return;
}
