/*
 * OutputDriver.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */
/*
 * JPL rules demonstrated (Logan)
 * Level 1:
 *  -Rule 1: Stick to language definition (ISO 11 for C and C++) DONE (show settings to display)
 *  -Rule 2: -WALL DONE (show settings to display)
 * Level 2:
 *  -Rule 6: use IPC to communicate between tasks DONE
 * Level 3:
 * 	-Rule 16: The use of Assertions. DONE look at any function over 10 lines
 * Level 4:
 * 	-Rule 21: Macros shall not be #define'd within a function or a block. DONE (display by using ctrl + f and looking up #define)
 * 	-Rule 22: #undef shall not be used. DONE (display by using ctrl + f and looking up #undef)
 * 	-Rule 31: #include directives in a file shall only be preceded by other preprocessor directives or comments. DONE
 */

#include <cstdint>
#include <cassert>

#include "main.h"
#include "math.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_dac.h"

//custom includes
#include "cpp_main.h"
#include "Queue.h"
#include "OutputDriver.h"
#include "displayQueue.h"
#include "Queue.h"


extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;

//TESTING FOR cpp_main();
/*
	inputQueue inputC;

	displayQueue OLED_Queue;

	waveQueue waveQueue;

	Channel channel = Channel(&inputC,&waveQueue);

	OutputDriver Signal = OutputDriver(&waveQueue,&OLED_Queue);

	OLED display = OLED(&OLED_Queue);

	nextState ns;
	ns.sw_select = 1; //channel 1
    ns.knobA = 1; //amplitude = 0.2
    ns.knobF = 0; //frequency = 50 Hz
    ns.knobD = 0;
    ns.btn_S = 1;
//	waveProp signal;
//	signal.amplitude1 = 4095;
//	signal.frequency1 = 1000;
//	signal.type1 = square;
//
//	signal.amplitude2 = 2045;
//	signal.frequency2 = 900;
//	signal.type2 = sine;
//	signal.delay = 0;
//
//	signal.channel = 1;
//	waveQueue.enqueue(signal);

//    inputC.enqueue(ns);

    channel.updateChannel();

	Signal.update_Channel();

	display.updateDisplay();

	uint32_t count_1ms = ONE_S;
	uint32_t count_5ms = 5;
	uint32_t count_10ms = 2;

	while(1)
	{
		if(count_1ms == 0)
		{
			count_5ms--;
			if(count_5ms != 0)
			{
				ns.knobF = 1;
				ns.knobA = 0; //amplitude = 0.2

			    inputC.enqueue(ns);

			    channel.updateChannel();

				Signal.update_Channel();

				display.updateDisplay();

				count_1ms = ONE_S;
			}
			count_1ms = ONE_S;
		}

		if(count_5ms == 0)
		{
			count_10ms--;

			if(count_10ms != 0)
			{
				ns.knobF = -1;

			    inputC.enqueue(ns);

			    channel.updateChannel();

				Signal.update_Channel();

				display.updateDisplay();

			}
			count_5ms = 5;

		}

		if(count_10ms == 0)
		{
			if(ns.sw_select == 1)
				ns.sw_select = 2;
			else
				ns.sw_select = 1;

			ns.knobA = 1;

		    inputC.enqueue(ns);

		    channel.updateChannel();

			Signal.update_Channel();

			display.updateDisplay();

			count_10ms = 2;

		}


		count_1ms--;
	}

*/


OutputDriver::OutputDriver(waveQueue* wQ, displayQueue* dQ) // @suppress("Class members should be properly initialized")
{
	oledQueue = dQ;
	signalQueue = wQ;
	freq1 = 100;
	amp1 = 2048;
	shape1 = sine;
	autoReload1 = 2731;

	oldFreq1 = freq1;
	oldAmp1 = amp1;
	oldShape1 = shape1;

	freq2 = 100;
	amp2 = 2048;
	shape2 = sine;
	autoReload2 = 2731;
	offset = 0;

	oldFreq2 = freq2;
	oldAmp2 = amp2;
	oldShape2 = shape2;

	oldFreq2_Delay = freq2;

	channel = 1;

	assert(channel == 1);

	calculateAutoReload1();
	setAutoReload(&htim2,1);
	generateWave(1);

	calculateAutoReload2();
	setAutoReload(&htim6,2);
	generateWave(2);

	HAL_TIM_Base_Start(&htim2);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave1, SIZE, DAC_ALIGN_12B_R);

	HAL_TIM_Base_Start(&htim6);
	HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave2, SIZE, DAC_ALIGN_12B_R);

	pack();
	oledQueue->enqueue(dValues);
}

void OutputDriver::resetCounter(TIM_HandleTypeDef* timer)
{
	if((timer != &htim2) && (timer != &htim6))
		return;
	(timer)->Instance->CNT = 0;
}

//setting the Auto Reload value
void OutputDriver::setAutoReload(TIM_HandleTypeDef* timer,uint8_t chan)
{
	if((timer != &htim2) && (timer != &htim6))
		return;

	if((chan != 1) && chan != 2)
		return;

	if(chan == 1)
	{
	    (timer)->Instance->ARR = (autoReload1);
	    (timer)->Init.Period = (autoReload1);
		return;
	}
	if(chan == 2)
	{
	    (timer)->Instance->ARR = (autoReload2);
	    (timer)->Init.Period = (autoReload2);
		return;
	}

}

void OutputDriver::setAttributes1(waveProp signal)
{
	shape1 = signal.type1;
	freq1 = signal.frequency1;
	amp1 = signal.amplitude1;
	return;
}

void OutputDriver::setAttributes2(waveProp signal)
{
	shape2 = signal.type2;
	freq2 = signal.frequency2;
	amp2 = signal.amplitude2;
	return;
}

void OutputDriver::calculateAutoReload1() //Period of the signal //TODO: add an assert
{
	uint32_t trig1 = 0;
	trig1 = freq1 * (SIZE) * (4 + 1);
	autoReload1 = ((CPU_CLK/trig1) - 1); //TODO:find a way to avoid division
	return;
}

void OutputDriver::calculateAutoReload2() //Period of the signal //TODO: add an assert
{
	uint32_t trig2 = 0;
	trig2 = freq2 * (SIZE) * (4 + 1);
	autoReload2 = ((CPU_CLK/trig2) - 1); //TODO:find a way to avoid division
	return;
}


void OutputDriver::update_Channel()
{
	waveProp signal;
	bool notEmpty = signalQueue->dequeue(&signal);
	//checking that there are values to dequeue

	if(notEmpty == false)
		return;

	channel = signal.channel;

	////////////////////Testing dequeued value//////////////////////
	if((signal.frequency1 > 0 && signal.frequency1 <= 1000) && (signal.amplitude1 > 0 && signal.amplitude1 < 4033) && (signal.type1 >= 0 && signal.type1 < 3) && (signal.delay >= 0 && signal.delay < 8))
	{
		GPIOB->ODR |= (1 << 5);// PB_5
		GPIOB->ODR &= ~(1 << 4); //PB_4
	}
	else
	{
		GPIOB->ODR |= (1 << 4); //PB_4
		GPIOB->ODR &= ~(1 << 5);// PB_5

		return;
	}
	////////////////////Testing dequeued value//////////////////////
	setAttributes1(signal);
	setAttributes2(signal);

	if(freq1 != oldFreq1 || amp1 != oldAmp1 || shape1 != oldShape1)
	{
		oldFreq1 = freq1;
		oldAmp1 = amp1;
		oldShape1 = shape1;

		calculateAutoReload1();

		setAutoReload(&htim2,1);
		generateWave(1);

		resetCounter(&htim2);
	}


	if((freq2 != oldFreq2 || amp2 != oldAmp2 || shape2 != oldShape2) && shape2 != delay)
	{

		oldFreq2 = freq2;
		oldAmp2 = amp2;
		oldShape2 = shape2;


		calculateAutoReload2();

		setAutoReload(&htim6,2);
		generateWave(2);

		resetCounter(&htim6);
	}


	if(shape2 == delay && oldShape2 != delay)
	{

		oldShape2 = delay;
		offset = signal.delay;
		oldFreq2_Delay = freq1;

		generateWave(1);

		setAutoReload(&htim2,1);
		setAutoReload(&htim6,1);
		delaySet();


		resetCounter(&htim6);
		resetCounter(&htim2);

		HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave1, SIZE, DAC_ALIGN_12B_R);

		HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave2, SIZE, DAC_ALIGN_12B_R);
	}

	else if(shape2 == delay && oldShape2 == delay)
	{
		offset = signal.delay;

		delaySet();

		setAutoReload(&htim6,1);

		resetCounter(&htim6);
		resetCounter(&htim2);

		if(oldFreq2_Delay != freq1)
		{
			oldFreq2_Delay = freq1;
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave1, SIZE, DAC_ALIGN_12B_R);

			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave2, SIZE, DAC_ALIGN_12B_R);
		}

	}

	if(offset != signal.delay && shape2 == delay)
		delaySet();

	if(shape1 == shape2 && oldShape1 != oldShape2)
	{
		oldShape1 = shape1;
		oldShape2 = shape2;

		resetCounter(&htim6);
		resetCounter(&htim2);

		HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
		HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);

		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave1, SIZE, DAC_ALIGN_12B_R);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave2, SIZE, DAC_ALIGN_12B_R);

	}


	pack();
	oledQueue->enqueue(dValues);
	assert(oledQueue != nullptr);
	return;


}

void OutputDriver::pack()
{
	dValues.F1 = freq1;
	dValues.A1 = amp1;
	dValues.type1 = shape1;

	dValues.F2 = freq2;
	dValues.A2 = amp2;
	dValues.type2 = shape2;

	dValues.channel = channel;
	dValues.offset = offset;
}

void OutputDriver::delaySet()
{
	uint32_t shift = offset * PHASE_SHIFT;
	assert(shift < SIZE);

	Queue shiftedWave;

	////////////////////Testing outWave value//////////////////////
	for(uint32_t i = 0; i < SIZE; i++)
	{
		shiftedWave.enqueue(outWave1[i]);

		if(outWave1[i] >= 0 && outWave1[i] < 4095)
		{
			GPIOB->ODR |= (1 << 3); //PB_3
		}
		else
		{
			GPIOB->ODR &= ~(1 << 3); //PB_3
		}
	}
	////////////////////Testing outWave value//////////////////////

	for(uint32_t i = 0; i < shift; i++)
	{
		uint32_t hold = 0;
		shiftedWave.dequeue(&hold);
		shiftedWave.enqueue(hold);
	}

	for(uint32_t i = 0; i < SIZE; i++)
	{
		shiftedWave.dequeue(&outWave2[i]);
	}
	return;
}

//Wave generation
void OutputDriver::generateWave(uint8_t chan)
{
	assert((chan > 0) && (chan < 3));
	if(chan == 1)
	{
		if(shape1 == sine)
			for(uint32_t i = 0; i < 255; i++)
				outWave1[i] = (amp1 * sineWave[i])/3971;

		else if(shape1 == square)
			for(uint32_t i = 0; i < SIZE; i++)
				outWave1[i] = (amp1 * squareWave[i])/MAX_SIZE;

		else if(shape1 == pulse)
			for(uint32_t i = 0; i < SIZE; i++)
				outWave1[i] = (amp1 * pulseWave[i])/MAX_SIZE;
		return;
	}

	if(chan == 2)
	{
		if(shape2 == sine)
			for(uint32_t i = 0; i < SIZE; i++)
				outWave2[i] = (amp2 * sineWave[i])/3971;

		else if(shape2 == square)
			for(uint32_t i = 0; i < SIZE; i++)
				outWave2[i] = (amp2 * squareWave[i])/MAX_SIZE;

		else if(shape2 == pulse)
			for(uint32_t i = 0; i < SIZE; i++)
				outWave2[i] = (amp2 * pulseWave[i])/MAX_SIZE;
		return;
	}

}

