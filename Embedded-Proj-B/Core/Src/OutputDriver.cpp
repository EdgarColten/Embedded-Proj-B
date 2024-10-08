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


void OutputDriver::setShape(wave chosenShape)
{
	shape = chosenShape;
	return;
}

//setting the Auto Reload value
void OutputDriver::setAutoReload(TIM_HandleTypeDef* timmer)
{
    (timmer)->Instance->ARR = (autoReload);
    (timmer)->Init.Period = (autoReload);
	return;
}


void OutputDriver::update_Channel(uint32_t newFreq, uint32_t newAmp, wave chosenShape) //TODO: take a struct opposed to individual values
{
	if(channel == 1)
	{
		shape = chosenShape;

		if(shape == sine && updateSine == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sineWave, SIZE, DAC_ALIGN_12B_R);
			updateSine = true;
		}
		else if(shape == sine && updateSine == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division

				setAutoReload(&htim2);
				generateWave();

			}
		}

		else if(shape == square && updateSquare == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
			setAutoReload(&htim2);

			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, squareWave, SIZE, DAC_ALIGN_12B_R);
			updateSquare = true;

		}
		else if(shape == square && updateSquare == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				amp = newAmp;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division

				setAutoReload(&htim2);
				generateWave();

			}
		}

		else if(shape == pulse && updatePulse == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, pulseWave, SIZE, DAC_ALIGN_12B_R);
			updatePulse = true;

		}
		else if(shape == pulse && updatePulse == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				amp = newAmp;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
				setAutoReload(&htim2);
				generateWave();
			}
		}
		return;
	}
	else if(channel == 2)
	{
		shape = chosenShape;

		if(shape == sine && updateSine == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, sineWave, SIZE, DAC_ALIGN_12B_R);
			updateSine = true;
		}
		else if(shape == sine && updateSine == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(shape == square && updateSquare == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
			setAutoReload(&htim6);

			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, squareWave, SIZE, DAC_ALIGN_12B_R);
			updateSquare = true;

		}
		else if(shape == square && updateSquare == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				amp = newAmp;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(shape == pulse && updatePulse == false)
		{
			freq = newFreq;
			amp = newAmp;
			uint32_t trig = 0;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, pulseWave, SIZE, DAC_ALIGN_12B_R);
			updatePulse = true;

		}
		else if(shape == pulse && updatePulse == true)
		{
			if(newFreq != freq || newAmp != amp)
			{
				uint32_t trig = 0;
				freq = newFreq;
				amp = newAmp;
				trig = freq * SIZE;
				autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
				setAutoReload(&htim6);
				generateWave();


			}
		}

		else if(shape == delay)
		{
			/*
			//generateDelay();
			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, pulseWave, SIZE, DAC_ALIGN_12B_R);
			*/
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
		uint32_t amplifier = amp * 1240;
		for(uint32_t i = 0; i < SIZE; i++)
		{
			sineWave[i] =  (sin(i*(2*PI)/SIZE) + 1) * (amplifier/2); //TODO:find a way to avoid division
		}
		return;
	}

	else if(shape == square)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			if(i < SIZE/2) //TODO:find a way to avoid division
			{
				squareWave[i] = 0;
			}
			else
			{
				squareWave[i] = amp * 1215; //1215 = 1 volt
				if(squareWave[i] > (MAX_SIZE - 1))
				{
					squareWave[i] = (MAX_SIZE - 1);
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
				pulseWave[i] = amp * 1240; //1215 = 1 volt
			}
			else
				pulseWave[i] = 0;
		}

		return;
	}

	else if(shape == delay)
	{
		return;
	}
}
