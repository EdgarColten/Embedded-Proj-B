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
		if(shapeCount < 4 && val > 0){
			shapeCount = shapeCount + val;
		}
		else if(shapeCount > 0 && val < 0){
			shapeCount = shapeCount + val;
		}

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

		case 3:
			myWaveProp.type = delay;
			break;
		default:
			break;
		return;
		}
	}

	void setFreq(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		uint8_t freqCount = 0;
		if(freqCount < 20 && val > 0){
			freqCount = freqCount + val;
		}
		else if(freqCount > 0 && val < 0){
			freqCount = freqCount + val;
		}
		switch(freqCount){
		case 0:
			myWaveProp.frequency = 1;
			break;
		case 1:
			myWaveProp.frequency = 50;
			break;
		case 2:
			myWaveProp.frequency = 100;
			break;
		case 3:
			myWaveProp.frequency = 150;
			break;
		case 4:
			myWaveProp.frequency = 200;
			break;
		case 5:
			myWaveProp.frequency = 250;
			break;
		case 6:
			myWaveProp.frequency = 300;
			break;
		case 7:
			myWaveProp.frequency = 350;
			break;
		case 8:
			myWaveProp.frequency = 400;
			break;
		case 9:
			myWaveProp.frequency = 450;
			break;
		case 10:
			myWaveProp.frequency = 500;
			break;
		case 11:
			myWaveProp.frequency = 550;
			break;
		case 12:
			myWaveProp.frequency = 600;
			break;
		case 13:
			myWaveProp.frequency = 650;
			break;
		case 14:
			myWaveProp.frequency = 700;
			break;
		case 15:
			myWaveProp.frequency = 750;
			break;
		case 16:
			myWaveProp.frequency = 800;
			break;
		case 17:
			myWaveProp.frequency = 850;
			break;
		case 18:
			myWaveProp.frequency = 900;
			break;
		case 19:
			myWaveProp.frequency = 950;
			break;
		case 20:
			myWaveProp.frequency = 1000;
			break;
		default:
			myWaveProp.frequency = 1;
			break;
		}
			return;

	}

	void setAmp(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		myWaveProp.amplitude = myWaveProp.amplitude + val;
		uint8_t ampCount = 0;
		if(ampCount < 33 && val > 0){
			ampCount = ampCount + val;
		}
		else if(ampCount > 0 && val < 0){
			ampCount = ampCount + val;
		}
		switch(ampCount){
		case 0:
			myWaveProp.amplitude = 0.1;
			break;
		case 1:
			myWaveProp.amplitude = 0.2;
			break;
		case 2:
			myWaveProp.amplitude = 0.3;
			break;
		case 3:
			myWaveProp.amplitude = 0.3;
			break;
		case 4:
			myWaveProp.amplitude = 0.4;
			break;
		case 5:
			myWaveProp.amplitude = 0.5;
			break;
		case 6:
			myWaveProp.amplitude = 0.6;
			break;
		case 7:
			myWaveProp.amplitude = 0.7;
			break;
		case 8:
			myWaveProp.amplitude = 0.8;
			break;
		case 9:
			myWaveProp.amplitude = 0.9;
			break;
		case 10:
			myWaveProp.amplitude = 1.0;
			break;
		case 11:
			myWaveProp.amplitude = 1.1;
			break;
		case 12:
			myWaveProp.amplitude = 1.2;
			break;
		case 13:
			myWaveProp.amplitude = 1.3;
			break;
		case 14:
			myWaveProp.amplitude = 1.4;
			break;
		case 15:
			myWaveProp.amplitude = 1.5;
			break;
		case 16:
			myWaveProp.amplitude = 1.6;
			break;
		case 17:
			myWaveProp.amplitude = 1.7;
			break;
		case 18:
			myWaveProp.amplitude = 1.8;
			break;
		case 19:
			myWaveProp.amplitude = 1.9;
			break;
		case 20:
			myWaveProp.amplitude = 2.0;
			break;
		case 21:
			myWaveProp.amplitude = 2.1;
			break;
		case 22:
			myWaveProp.amplitude = 2.2;
			break;
		case 23:
			myWaveProp.amplitude = 2.3;
			break;
		case 24:
			myWaveProp.amplitude = 2.4;
			break;
		case 25:
			myWaveProp.amplitude = 2.5;
			break;
		case 26:
			myWaveProp.amplitude = 2.6;
			break;
		case 27:
			myWaveProp.amplitude = 2.7;
			break;
		case 28:
			myWaveProp.amplitude = 2.8;
			break;
		case 29:
			myWaveProp.amplitude = 2.9;
			break;
		case 30:
			myWaveProp.amplitude = 3.0;
			break;
		case 31:
			myWaveProp.amplitude = 3.1;
			break;
		case 32:
			myWaveProp.amplitude = 3.2;
			break;
		case 33:
			myWaveProp.amplitude = 3.3;
			break;
		default:
			myWaveProp.amplitude = 0.1;
			break;
		}
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



