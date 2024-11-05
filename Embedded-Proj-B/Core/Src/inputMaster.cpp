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
		4: Do not use task delays for task synchronization.
		7: Do not use direct or indirect recursion
		10 Use memory protection, safety margins, barrier patterns
		12: Do not use selective value assignments to elements of an enum list
Level 3:
		13: Declare data objects at smallest possible level of scope
		14: Check the return value of non-void functions, or explicitly cast to (void)
		15: Check the validity of values passed to functions

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
