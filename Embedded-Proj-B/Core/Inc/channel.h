/*
 * channel.h
 *
 *  Created on: Oct 22, 2024
 *      Author: credgar21
 */
/**
 * @file	channel.h
 * @brief	This class is the equation layer for each channel
 * that recieves the incremental value from the input queue
 * to determine what the displayed value of amplitude, frequency, shape, and delay should be.
 * Equation produces the value of each parameter as a value specified for the display
 * not necessarily the actual value recognized by the user
 */
#include "cpp_main.h"

#include "inputQueue.h"
#include "waveQueue.h"

#ifndef INC_CHANNEL_H_
#define INC_CHANNEL_H_

#include "cpp_main.h"



class Channel{
	/*
	 *  // @suppress("Miss copy constructor or assignment operator")
	 *  //
	 */

	inputQueue *Input_q;
	waveQueue *Wave_q;

	waveProp previousValues;
	waveProp myWaveProp;

	uint8_t shapeCount1;
	uint8_t freqCount1;
	uint8_t ampCount1;

	uint8_t shapeCount2;
	uint8_t freqCount2;
	uint8_t ampCount2;

	uint8_t delayCount;
	uint8_t chanCount;
	nextState ns;

public:

	Channel(inputQueue*, waveQueue*);

	/*
	 * @brief Takes input from the button S to determine what step the channels shape should be on and interprets the shape based on that step
	 *
	 */
	void setWaveType();
	/*
	 * @brief Takes input from the knob F to determine what step the knob should be on and interprets the frequency based on that step
	 *
	 */
	void setFreq();
	/*
	 * @brief Takes input from the knob A to determine what step the knob should be on and interprets the amplitude based on that step
	 *
	 */
	void setAmp();
	/*
	 * @brief Takes input from the knob D to determine what step the knob should be on and interprets the delay based on that step
	 *
	 */
	void setDelay();
	/*
	 * @brief Runs each set function described above if there is an update from the input driver. This functions sets all values of the above variables to the classes waveProp struct and enqueues it to the Wave Queue used by the display
	 *
	 */
	void updateChannel();
//	void cpChannel(waveProp);
};



#endif /* INC_CHANNEL_H_ */
