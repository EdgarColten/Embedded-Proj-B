/*
 * inputMaster.h
 *
 *  Created on: Oct 15, 2024
 *      Author: color
 */

/**
 * @file	inputMaster.h
 * @brief	Handles all input drivers return values
 *
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
class inputMaster { // @suppress("Miss copy constructor or assignment operator")
	inputQueue* channel;

	Semaphore* sem;
	inputBtn shape_btn = inputBtn(shape_btn_GPIO_Port,10);
	inputSlide channel_Select = inputSlide(channel_select_sw_GPIO_Port,9);
	inputDriver freq_knob = inputDriver(Freq_knob_A_GPIO_Port,Freq_knob_B_GPIO_Port,12,0);
	inputDriver amp_knob = inputDriver(Amp_knob_A_GPIO_Port, Amp_knob_B_GPIO_Port, 7, 6);
	inputDriver delay_knob = inputDriver(GPIOB, GPIOA,1,11);

	nextState nState;

	//Defaults
	int8_t currentChannel;
	int8_t freq;
	int8_t amp;
	int8_t delay;
	int8_t shape;
public:
	inputMaster(inputQueue*, Semaphore*);//Constructor
	/**
	 * @brief Gets values of user-defined input pins and sends them to inputQueue
	 */
	void update();

	/**
	 * @brief Packs input driver return values into a nextState struct (defined in cpp_main.h) to be used by class inputQueue
	 *
	 */
	void masterGet();

};

#endif /* SRC_INPUTMASTER_H_ */
