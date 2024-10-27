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
 * Level 3:
 * 	-Rule 16: The use of Assertions. TODO
 * 	-Rule :
 * Level 4:
 * 	-Rule 21: Macros shall not be #define'd within a function or a block. TODO (display by using ctrl + f and looking up #define)
 * 	-Rule 22: #undef shall not be used. TODO (display by using ctrl + f and looking up #undef)
 * 	-Rule 31: #include directives in a file shall only be preceded by other preprocessor directives or comments. TODO
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
#include "SSD1306_I2C_Driver.h"
#include "displayQueue.h"
#include "Queue.h"


extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;


//NOTE: 3.3v = 4095
//NOTE: 1v = 1240
//NOTE: 272 = 1 kHz
//NOTE: 2731 = 100 Hz

//TESTING FOR cpp_main();
/*

	displayQueue OLED_Queue1;
	displayQueue OLED_Queue2;

	waveQueue waveQueue1;
	waveQueue waveQueue2;

	OutputDriver Channel1 = OutputDriver(1,&waveQueue1,&OLED_Queue1);
	OutputDriver Channel2 = OutputDriver(2,&waveQueue2,&OLED_Queue2);

	OLED display1 = OLED(1,&OLED_Queue1);
	OLED display2 = OLED(2,&OLED_Queue2);

	waveProp signal1;
	signal1.amplitude = 2;
	signal1.frequency = 1;
	signal1.type = square;
	signal1.delay = 0;

	waveProp signal2;
	signal2.amplitude = 1;
	signal2.frequency = 830;
	signal2.type = sine;
	signal2.delay = 3;


	Channel1.update_Channel(signal1, Channel1);
	Channel2.update_Channel(signal2, Channel1);


	display1.updateDisplay();
	display2.updateDisplay();

	Channel1.update_Channel(signal1, Channel1);
	Channel2.update_Channel(signal2, Channel1);


	signal2.type = pulse;
	signal2.frequency = 764;
	Channel2.update_Channel(signal2, Channel1);
	display2.updateDisplay();


	signal1.type = sine;
	signal1.frequency = 84;
	Channel1.update_Channel(signal1, Channel1);
	display1.updateDisplay();

	signal2.type = delay;
	signal2.delay = 5;
	Channel2.update_Channel(signal2, Channel1);
	display2.updateDisplay();

	Channel2.update_Channel(signal2, Channel1);
	display2.updateDisplay();


*/


OutputDriver::OutputDriver(uint8_t chan, waveQueue* wQ, displayQueue* dQ) // @suppress("Class members should be properly initialized")
{
	oledQueue = dQ;
	signalQueue = wQ;
	freq = 1;
	amp = 1;
	offset = 0;
	shape = sine;
	autoReload = 2731;
	channel = chan;
}


//setting the Auto Reload value
void OutputDriver::setAutoReload(TIM_HandleTypeDef* timer)
{

	//TODO: improve tests and assertions
    (timer)->Instance->ARR = (autoReload);
    (timer)->Init.Period = (autoReload);
	return;
}

void OutputDriver::setAttributes(waveProp signal)
{
	//TODO: improve tests and assertions
	assert(signal.amplitude > 0);
	assert(signal.frequency > 0);

	shape = signal.type;
	freq = signal.frequency;
	amp = signal.amplitude;

	return;
}

void OutputDriver::calculateAutoReload() //Period of the signal
{
	uint32_t trig = 0;
	trig = freq * (SIZE);
	autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
	return;
}

void OutputDriver::getAttributes(waveProp* dataPoll)
{
	assert(dataPoll != nullptr);

	dataPoll->amplitude = amp;
	dataPoll->frequency = freq;
	dataPoll->type = shape;

	return;
}

void OutputDriver::update_Channel(OutputDriver channel1) //TODO: take out struct and just use queue attribute
{
	waveProp signal;

	//sanity check
	assert(signalQueue != nullptr);

	bool notEmpty = signalQueue->dequeue(&signal);
	//checking that there are values to dequeue

	if(notEmpty == false)
		return;


	////////////////////Testing dequeued value//////////////////////
	if((signal.frequency > 0 && signal.frequency <= 1000) && (signal.amplitude > 0 && signal.amplitude < 4096) && (signal.type >= 0 && signal.type < 4) && (signal.delay >= 0 && signal.delay < 8))
	{
		GPIOA->ODR |= (1 << 3);// PA_3
		GPIOA->ODR &= ~(0 << 1); //PA_1
	}

	else
	{
		GPIOA->ODR |= (1 << 1); //PA_1
		GPIOA->ODR &= ~(1 << 3);// PA_3

		return;
	}
	////////////////////Testing dequeued value//////////////////////


	if((freq != signal.frequency || amp != signal.amplitude || shape != signal.type) && signal.type != delay)
	{
		if(channel == 1)
		{
			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

			assert(oledQueue != nullptr);

			pack();
			oledQueue->enqueue(dValues);

			return;
		}

		else if(channel == 2)
		{

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

			assert(oledQueue != nullptr);

			pack();
			oledQueue->enqueue(dValues);


			return;
		}
	}

	else if(signal.type == delay)
	{
		waveProp data; //local
		channel1.getAttributes(&data);

		if(freq != data.frequency || amp != data.amplitude || shape != data.type || offset != signal.delay)
		{

			offset = signal.delay;
			setAttributes(data);

			calculateAutoReload();
			setAutoReload(&htim6);
			generateWave();

			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);

			HAL_TIM_Base_Start(&htim6);
			HAL_TIM_Base_Start(&htim2);

			if(offset == 0)
			{
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
			}
			else if(offset > 0 && offset < 8)
			{
				delaySet();
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, delayOutWave, SIZE, DAC_ALIGN_12B_R);
			}
			assert(oledQueue != nullptr);

			pack();
			oledQueue->enqueue(dValues);
			return;
		}

		else
			return;
	}

	else
		return;
}

void OutputDriver::pack()
{
	dValues.F = freq;
	dValues.type = shape;
	dValues.channel = channel;
}

void OutputDriver::delaySet()
{
	uint32_t shift = offset * PHASE_SHIFT;
	assert(shift >= 0);

	Queue shiftedWave;

	for(uint32_t i = 0; i < SIZE; i++)
	{
		assert(shiftedWave.enqueue(outWave[i]) == true);
		if(outWave[i] >= 0 && outWave[i] < 4095)
		{
			GPIOB->ODR |= (1 << 3); //PB_3
		}
		else
			GPIOB->ODR &= ~(1 << 3); //PB_3
	}

	for(uint32_t i = 0; i < shift; i++)
	{
		uint32_t hold = 0;
		shiftedWave.dequeue(&hold);
		assert(hold >= 0);
		shiftedWave.enqueue(hold);
	}

	for(uint32_t i = 0; i < SIZE; i++)
	{
		//uint32_t holdNewValue = 0;
		assert(shiftedWave.dequeue(&delayOutWave[i]) == true);
	}

	return;
}

//Wave generation
void OutputDriver::generateWave()
{
	if(shape == sine)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			outWave[i] =  ((sin(i*(2*PI)/SIZE) + 1) * (amp/2)); //TODO:find a way to avoid division
		}
		return;
	}

	else if(shape == square)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			if(i < SIZE/2) //TODO:find a way to avoid division
			{
				outWave[i] = 0;
			}
			else
			{
				outWave[i] = amp; //1215 = 1 volt
				if(outWave[i] > (MAX_SIZE - 1))
				{
					outWave[i] = (MAX_SIZE - 1);
				}
			}

		}

		return;
	}

	else if(shape == pulse)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			if((i%10) == 0 && i != 0) //TODO:find a way to avoid division
			{
				outWave[i] = amp; //1215 = 1 volt
			}
			else
				outWave[i] = 0;
		}

		return;
	}

}

