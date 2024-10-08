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


#define ARRAY_SIZE 4

extern "C" void cpp_main(void);

class Channel { // @suppress("Miss copy constructor or assignment operator")
private:
	Queue* queue;

	//Might be able to be replaced with a Queue*
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
			myWaveProp.type = sine;
			break;

		case 1:
			myWaveProp.type = square;
			break;


		case 2:
			myWaveProp.type = pulse;
			break;

		default:
			break;
		return;
		}
	}

	void setFreq(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		myWaveProp.frequency = myWaveProp.frequency + val;
		return;
	}

	void setAmp(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		myWaveProp.amplitude = myWaveProp.amplitude + val;
		return;
	}

	void setDelay(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
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

	void cpChannel(waveProp x){ //x is ch1 so the delay value should be 0. This may not give the correct delay
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

	waveProp dequeueWave(){ //this needs to be a pointer so that there isn't any direct interaction between modules
		waveProp sendingStruct;
		sendingStruct = channelQueue[qHead];
		qHead++;
		if(qHead>ARRAY_SIZE){
			qHead = 0;
		}

		return sendingStruct;
	}
};



