/*
 * OutputDriver.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "math.h"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_dac.h"

//custom includes
#include "cpp_main.h"
#include "Queue.h"
#include "OutputDriver.h"
#include "SSD1306_I2C_Driver.h"


extern DAC_HandleTypeDef hdac1;
//extern DMA_HandleTypeDef hdma_dac_ch1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;


//NOTE: 3.3v = 4095
//NOTE: 1v = 1215
//NOTE: 272 = 1 kHz
//NOTE: 2731 = 100 Hz

//TESTING FOR cpp_main();
/*
	waveProp signal1;
	signal1.amplitude = 2;
	signal1.frequency = 1000;
	signal1.type = sine;
	signal1.delay = 0;

	waveProp signal2;
	signal2.amplitude = 1;
	signal2.frequency = 250;
	signal2.type = delay;
	signal2.delay = 1;

	OutputDriver Channel1 = OutputDriver(1);
	OutputDriver Channel2 = OutputDriver(2);

	Channel1.update_Channel(signal1, Channel1);
	Channel2.update_Channel(signal2, Channel1);

*/



OutputDriver::OutputDriver(uint8_t chan) // @suppress("Class members should be properly initialized")
{
	freq = 1;
	amp = 1;
	shape = sine;
	autoReload = 2731;
	channel = chan;

	//update_Channel(freq,amp,shape);	//Generation check objects
	updateSine = false;
	updateSquare = false;
	updatePulse = false;
	updateDelay = false;
}


wave OutputDriver::getShape()
{
	return shape;
}

//setting the Auto Reload value
void OutputDriver::setAutoReload(TIM_HandleTypeDef* timmer)
{
    (timmer)->Instance->ARR = (autoReload);
    (timmer)->Init.Period = (autoReload);
	return;
}

void OutputDriver::setAttributes(waveProp signal)
{
	freq = signal.frequency;
	amp = signal.amplitude;
}

void OutputDriver::calculateAutoReload(uint32_t delay)
{
	uint32_t trig = 0;
	trig = freq * SIZE;
	autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
	return;
}



void OutputDriver::getAttributes(waveProp* dataPoll)
{
	dataPoll->amplitude = amp;
	dataPoll->frequency = freq;
	dataPoll->type = shape;

	return;
}


void OutputDriver::update_Channel(waveProp signal, OutputDriver channel1) //TODO: take a struct opposed to individual values
{
	if(channel == 1)
	{
		//shape = signal.type;

		//if(shape == sine && updateSine == false)
		if(signal.type == sine && updateSine == false)

		{
			shape = sine;

			freq = signal.frequency;
			amp = signal.amplitude;

			calculateAutoReload(signal.delay);

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
			updateSine = true;
		}
		else if(signal.type == sine && updateSine == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = sine;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);

				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				setAutoReload(&htim2);
				generateWave();

			}
		}

		else if(signal.type == square && updateSquare == false)
		{
			shape = square;
			freq = signal.frequency;
			amp = signal.amplitude;
			calculateAutoReload(signal.delay);

			setAutoReload(&htim2);

			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
			updateSquare = true;

		}
		else if(signal.type == square && updateSquare == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = square;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);


				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim2);
				generateWave();

			}
		}

		else if(signal.type == pulse && updatePulse == false)
		{
			shape = pulse;
			freq = signal.frequency;
			amp = signal.amplitude;
			calculateAutoReload(signal.delay);

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
			updatePulse = true;

		}
		else if(signal.type == pulse && updatePulse == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = pulse;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);

				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				setAutoReload(&htim2);
				generateWave();
			}
		}
		return;
	}
	else if(channel == 2)
	{
		//HAL_DAC_Stop(&hdac1, DAC1_CHANNEL_2);
		if(signal.type == sine && updateSine == false)
		{
			shape = sine;
			freq = signal.frequency;
			amp = signal.amplitude;
			calculateAutoReload(signal.delay);

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
			updateSine = true;
		}
		else if(signal.type == sine && updateSine == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = sine;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(signal.type == square && updateSquare == false)
		{
			shape = square;
			freq = signal.frequency;
			amp = signal.amplitude;
			calculateAutoReload(signal.delay);

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
			updateSquare = true;

		}
		else if(signal.type == square && updateSquare == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = square;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(signal.type == pulse && updatePulse == false)
		{
			shape = pulse;
			freq = signal.frequency;
			amp = signal.amplitude;
			calculateAutoReload(signal.delay);

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
			updatePulse = true;

		}
		else if(signal.type == pulse && updatePulse == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
				shape = pulse;
				freq = signal.frequency;
				amp = signal.amplitude;
				calculateAutoReload(signal.delay);

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(signal.type == delay)
		{
			waveProp data;
			channel1.getAttributes(&data);

			switch(channel1.getShape())
			{
				case sine:
				{
					shape = sine;
					setAttributes(data);
					calculateAutoReload(signal.delay);
					setAutoReload(&htim6);
					generateWave();

					HAL_TIM_Base_Start(&htim6);
					HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

					return;
					break;
				}

				case square:
				{
					shape = square;
					setAttributes(data);
					calculateAutoReload(signal.delay);
					setAutoReload(&htim6);
					generateWave();

					HAL_TIM_Base_Start(&htim6);
					HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

					return;
					break;
				}

				case pulse:
				{
					shape = pulse;
					setAttributes(data);
					calculateAutoReload(signal.delay);
					setAutoReload(&htim6);
					generateWave();

					HAL_TIM_Base_Start(&htim6);
					HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
					return;
					break;
				}

				default:
					break;
			}

		}
		return;
	}
	else
		return;

}

//Wave generation

void OutputDriver::generateWave()
{
	if(shape == sine)
	{
		uint32_t amplifier = amp * 1215; //1215 = 1V
		for(uint32_t i = 0; i < SIZE; i++)
		{
			outWave[i] =  ((sin(i*(2*PI)/SIZE) + 1) * (amplifier/2)) - (delay/8); //TODO:find a way to avoid division
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

	else if(shape == delay)
	{
		return;
	}
}
