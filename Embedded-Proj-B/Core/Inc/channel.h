/*
 * channel.h
 *
 *  Created on: Oct 22, 2024
 *      Author: credgar21
 */

#include "cpp_main.h"

#include "inputQueue.h"
#include "waveQueue.h"

#ifndef INC_CHANNEL_H_
#define INC_CHANNEL_H_

#include "cpp_main.h"

class Channel{ // @suppress("Miss copy constructor or assignment operator")
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
	void setWaveType();
	void setFreq();
	void setAmp();
	void setDelay();
	void updateChannel();
//	void cpChannel(waveProp);
};



#endif /* INC_CHANNEL_H_ */
