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

/*
 * @brief	This class is the equation layer for each channel
 * that recieves the incremental value from the input queue
 * to determine what the displayed value of amplitude, frequency, shape, and delay should be.
 * Equation produces the value of each parameter as a value specified for the display
 * not necessarily the actual value recognized by the user
 */

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

	/*
	 * @brief A basic constructor for the Channel class
	 *
	 * @param inputQueue* a pointer to an instance of the inputQueue class, waveQueue* a ponter to the waveQueue struct containing variables for frequency, amplitude, shape,delay, and channel
	 * @return No return value only creates instance of class
	 */
	Channel(inputQueue*, waveQueue*);

	/*
	 * @brief Takes input from the button S to determine what step the channels shape should be on and interprets the shape based on that step
	 *
	 * @param No parameters but uses the ns.btn_S from the input class
	 * @return no return value but changes the value of shape in the channel class for either channel 1 or 2
	 */
	void setWaveType();
	/*
	 * @brief Takes input from the knob F to determine what step the knob should be on and interprets the frequency based on that step
	 *
	 * @param No parameters but uses the ns.knob_F from the input class
	 * @return no return value but changes the value of frequency in the channel class for either channel 1 or 2
	 */
	void setFreq();
	/*
	 * @brief Takes input from the knob A to determine what step the knob should be on and interprets the amplitude based on that step
	 *
	 * @param No parameters but uses the ns.knob_A from the input class
	 * @return no return value but changes the value of amplitude in the channel class for either channel 1 or 2
	 */
	void setAmp();
	/*
	 * @brief Takes input from the knob D to determine what step the knob should be on and interprets the delay based on that step
	 *
	 * @param No parameters but uses the ns.knob_D from the input class
	 * @return no return value but changes the value of delay in the channel class for channel 2
	 */
	void setDelay();
	/*
	 * @brief Runs each set function described above if there is an update from the input driver. This functions sets all values of the above variables to the classes waveProp struct and enqueues it to the Wave Queue used by the display
	 *
	 * @param No parameters are used but the bool value of dequeue with a parameter of next state is checked to see if the values need updated.
	 * @return	No return type. Function sets values of the classes frequency, amplitude, shape, delay, and channel number to be sent to Wave Queue which will be used by the display classes.
	 */
	void updateChannel();
//	void cpChannel(waveProp);
};



#endif /* INC_CHANNEL_H_ */
