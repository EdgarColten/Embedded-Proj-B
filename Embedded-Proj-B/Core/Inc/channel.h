/*
 * channel.h
 *
 *  Created on: Oct 22, 2024
 *      Author: credgar21
 */

#ifndef INC_CHANNEL_H_
#define INC_CHANNEL_H_

#include "cpp_main.h"

class Channel{
	waveProp myWaveProp;
	uint8_t shapeCount;
	uint8_t freqCount;
	uint8_t ampCount;
	uint8_t delayCount;
public:
	waveProp getMyWaveProp(void);
	void setWaveType(int8_t);
	void setFreq(int8_t);
	void setAmp(int8_t);
	void setDelay(int8_t);
	void updateChannel(nextState);
//	void cpChannel(waveProp);
};



#endif /* INC_CHANNEL_H_ */
