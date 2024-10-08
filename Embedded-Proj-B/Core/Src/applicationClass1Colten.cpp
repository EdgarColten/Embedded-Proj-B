/*
 * main_cpp_Colten.cpp
 *
 *  Created on: Sep 27, 2024
 *      Author: credgar21
 */

#include <cstdint>

#define ARRAY_SIZE 4

extern "C" void cpp_main(void);

class Channel {
private:
/** **		enum waveType {Sine,Square,Pulse};
	*
	*	struct waveProp {
	*
	*	uint32_t freq;
	*	uint32_t amp;
	*	uint32_t delay;
	*	enum waveType shape;
	*	}myWaveProp;
**/
	int8_t queueCount = 0;
	int8_t qHead = 0;
	int8_t qTail = 0;

	waveProp myWaveProp;
	waveProp channelQueue[ARRAY_SIZE];

public:

	void setWaveType(uint8_t val){
		uint8_t shapeCount = 0;
		switch(shapeCount){

		case 0:
			type = sine;

		case 1:
			type = square;

		case 2:
			type = pulse;

		return;
		}
	}

	void setFreq(uint8_t val){
		myWaveProp.freq = myWaveProp.freq + val;
		return;
	}

	void setAmp(uint8_t val){
		myWaveProp.amp = myWaveProp.amp + val;
		return;
	}

	void setDelay(uint8_t val){
		int8_t delayCount = 0;
		if(val>0 && delayCount<7){
			myWaveProp.delay = myWaveProp.delay + val;
			delayCount++;
	}
		else if(val<0 && delayCount>0){
			myWaveProp.delay = myWaveProp.delay + val;
			delayCount--;
		}
		return;
	}

	void cpChannel(waveProp x){
		myWaveProp.type = x.type;
		myWaveProp.frequency = x.frequency;
		myWaveProp.amplitude = x.amplitude;
		myWaveProp.delay = x.delay;
	}

	void enqueueWave(waveProp sentStruct){

		if(qTail>ARRAY_SIZE){
			qTail = 0;
		}

		if(queueCount<ARRAY_SIZE){
			channelQueue[qTail] = sentStruct;
			qTail++;
		}

		return;
	}

	waveProp dequeueWave(){
		waveProp sendingStruct;
		sendingStruct = channelQueue[qHead];
		qHead++;
		if(qHead>ARRAY_SIZE){
			qHead = 0;
		}

		return sendingStruct;
	}
};



