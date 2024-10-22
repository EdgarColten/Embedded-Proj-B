/*
 * channel.h
 *
 *  Created on: Oct 22, 2024
 *      Author: credgar21
 */

#ifndef INC_CHANNEL_H_
#define INC_CHANNEL_H_

class Channel{
	waveProp myWaveProp;
public:
	void setWaveType(uint8_t);
	void setFreq(uint8_t);
	void setAmp(uint8_t);
	void setDelay(uint8_t);
	void cpChannel(waveProp);
};



#endif /* INC_CHANNEL_H_ */
