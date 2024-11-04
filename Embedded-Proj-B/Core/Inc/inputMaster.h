/*
 * inputMaster.h
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

#include "cpp_main.h"
#include "inputBtn.h"
#include "inputSlide.h"
#include "inputDriver.h"
#include "inputQueue.h"
#include "Semaphore.h"

#ifndef INC_INPUTMASTER_H_
#define INC_INPUTMASTER_H_
class inputMaster { //This class is the master input driver which takes 4 inputs and puts them into a struct to send to Q// // @suppress("Miss copy constructor or assignment operator")
	inputQueue* channel;

	Semaphore* sem;
	inputBtn shape_btn = inputBtn(shape_btn_GPIO_Port,10);
	inputSlide channel_Select = inputSlide(channel_select_sw_GPIO_Port,9);
	inputDriver freq_knob = inputDriver(Freq_knob_A_GPIO_Port,Freq_knob_B_GPIO_Port,12,0);
	inputDriver amp_knob = inputDriver(Amp_knob_A_GPIO_Port, Amp_knob_B_GPIO_Port, 7, 6);
	inputDriver delay_knob = inputDriver(Delay_knob_A_GPIO_Port, Delay_knob_B_GPIO_Port,11,10);

	nextState nState;

	//Defaults
	int8_t currentChannel;
	int8_t freq;
	int8_t amp;
	int8_t delay;
	int8_t shape;
public:
	inputMaster(inputQueue*, Semaphore*);
	void update();
	void masterGet();
};

#endif /* SRC_INPUTMASTER_H_ */
