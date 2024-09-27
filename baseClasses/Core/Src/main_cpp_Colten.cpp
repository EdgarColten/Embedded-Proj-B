/*
 * main_cpp_Colten.cpp
 *
 *  Created on: Sep 27, 2024
 *      Author: credgar21
 */

class Channel {
private:
	shape uint8_t;
	frequency uint32_t;
	amplitude uint16_t;
	delayC2 uint32_t;

public:

	uint8_t getShape(){
		return shape;
	}

	uint32_t getFreq(){
		return frequency;
	}

	uint16_t getAmp(){
		return amplitude;
	}

	void cpChannel(shape1,frequency1,amplitude1,delay1){
		shape = shape1;
		frequency = frequency1;
		amplitude = amplitude1;
		delayC2 = delay1;
	}
};



