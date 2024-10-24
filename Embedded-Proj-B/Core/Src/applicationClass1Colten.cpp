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

extern "C" void cpp_main(void);

class Channel { // @suppress("Miss copy constructor or assignment operator")
private:
	//Might be able to be replaced with a Queue*
	waveProp myWaveProp;
	uint8_t shapeCount = 0;
	uint8_t freqCount = 0;
	uint8_t ampCount = 0;
	int8_t delayCount = 0;

public:

	void setWaveType(uint8_t val){
		if(shapeCount < 3 && val > 0){
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
		if(freqCount < 20 && val > 0){
			freqCount = freqCount + val;
		}
		else if(freqCount > 0 && val < 0){
			freqCount = freqCount + val;
		}

		if(freqCount == 0){
			myWaveProp.frequency = 1;
		}
		else{
			myWaveProp.frequency = 50*freqCount;
		}
			return;

	}

	void setAmp(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		if(ampCount < 33 && val > 0){
			ampCount = ampCount + val;
		}
		else if(ampCount > 0 && val < 0){
			ampCount = ampCount + val;
		}
		myWaveProp.amplitude = (ampCount * 0.1) + 0.1;

		return;
	}

	void setDelay(uint8_t val){ //when incrementing and decrementing this frequency you will need a cases for the position of the knobs
		if(val>0 && delayCount<7){
			delayCount = delayCount + val;
	}
		else if(val<0 && delayCount>0){
			delayCount = delayCount + val;
		}

		myWaveProp.amplitude = (delayCount/8) * 256;
		return;
	}

	void cpChannel(waveProp x){ //x is ch1 so the delay value should be 0. This may not give the correct delay
		myWaveProp.type = x.type;
		myWaveProp.frequency = x.frequency;
		myWaveProp.amplitude = x.amplitude;
		myWaveProp.delay = x.delay;
	}

};



