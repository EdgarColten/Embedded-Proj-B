/*
 * OutputDriver.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */
/*
 * JPL rules demonstrated (Logan)
 * Level 3:
 * 	-Rule 16: The use of Assertions.
 * 	-Rule :
 * 	-Rule :
 * Level 4:
 * 	-Rule 21: Macros shall not be #define'd within a function or a block.
 * 	-Rule 22: #undef shall not be used.
 * 	-Rule 31: #include directives in a file shall only be preceded by other preprocessor directives or comments.
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

	OutputDriver Channel1 = OutputDriver(1,&OLED_Queue1);
	OutputDriver Channel2 = OutputDriver(2,&OLED_Queue2);

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


OutputDriver::OutputDriver(uint8_t chan,displayQueue* dQ) // @suppress("Class members should be properly initialized")
{
	oledQueue = dQ;
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

void OutputDriver::update_Channel(waveProp signal, OutputDriver channel1) //TODO: take out struct and just use queue attribute
{
	//waveProp signal;
	//signalQueue.dequeue(&signal);
	if((freq != signal.frequency || amp != signal.amplitude || shape != signal.type) && signal.type != delay)
	{
		if(channel == 1)
		{
			waveProp testSignal;
			testSignal.amplitude = -1;
			testSignal.frequency = 0;

			setAttributes(testSignal);
			calculateAutoReload();

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

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
	Queue shiftedWave;

	for(uint32_t i = 0; i < SIZE; i++)
	{
		shiftedWave.enqueue(outWave[i]);
	}

	for(uint32_t i = 0; i < shift; i++)
	{
		uint32_t hold = 0;
		shiftedWave.dequeue(&hold);
		shiftedWave.enqueue(hold);
	}

	for(uint32_t i = 0; i < SIZE; i++)
	{
		//uint32_t holdNewValue = 0;
		shiftedWave.dequeue(&delayOutWave[i]);
	}

	return;
}

//Wave generation
void OutputDriver::generateWave()
{
	if(shape == sine)
	{
		uint32_t amplifier = amp * 1220; //1215 = 1V
		for(uint32_t i = 0; i < SIZE; i++)
		{
			outWave[i] =  ((sin(i*(2*PI)/SIZE) + 1) * (amplifier/2)); //TODO:find a way to avoid division
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
				outWave[i] = amp * 1215; //1215 = 1 volt
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
				outWave[i] = amp * 1215; //1215 = 1 volt
			}
			else
				outWave[i] = 0;
		}

		return;
	}

}

