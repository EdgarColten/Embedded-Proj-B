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
#include "Queue.h"
#include "OutputDriver.h"
#include "stm32l4xx_hal_dac.h"

extern DAC_HandleTypeDef hdac1;
extern DMA_HandleTypeDef hdma_dac_ch1;
extern TIM_HandleTypeDef htim2;


//NOTE: 3.3v = 4095
//NOTE: 1v = 1215
//NOTE: 272 = 1 kHz
//NOTE: 2731 = 100 Hz

#define PI 3.1415926535
#define MAX_SIZE 4096
#define SIZE 256
#define CPU_CLK 70000000
OutputDriver::OutputDriver()
{
	//HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
	//HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);

	freq = 100;
	amp = 1;
	shape = square;
	autoReload = 2731;
}




void OutputDriver::update_Channel(uint32_t newFreq, uint32_t newAmp)
{

	if(shape == sine)
	{
		uint32_t trig = 0;
		uint32_t sineWave[SIZE];
		generateSine(sineWave,SIZE);
		HAL_TIM_Base_Start(&htim2);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, sineWave, SIZE, DAC_ALIGN_12B_R);


		if(newFreq != freq || newAmp != amp)
		{
			freq = newFreq;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1);
			__HAL_TIM_SET_AUTORELOAD(&htim2,autoReload);

		}

	}

	else if(shape == square)
	{
		uint32_t squareWave[SIZE];
		uint32_t trig = 0;
		generateSquare(squareWave,SIZE);
		HAL_TIM_Base_Start(&htim2);
		HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, squareWave, SIZE, DAC_ALIGN_12B_R);

		if(newFreq != freq || newAmp != amp)
		{
			freq = newFreq;
			amp = newAmp;
			trig = freq * SIZE;
			autoReload = ((CPU_CLK/trig) - 1);
			__HAL_TIM_SET_AUTORELOAD(&htim2,autoReload);

		}


	}

	else if(shape == pulse)
	{

	}

	else if(shape == delay)
	{

	}

	return;
}



void OutputDriver::generateSine(uint32_t* sineWave,uint16_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		sineWave[i] = amp * (sin(i*(2*PI)/size) + 1) * (MAX_SIZE/2);
	}
	return;

}


void OutputDriver::generateSquare(uint32_t* squareWave,uint16_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		if(i < size/2)
		{
			squareWave[i] = 0;
		}
		else
			squareWave[i] = amp * 1215;
	}

	return;
}
