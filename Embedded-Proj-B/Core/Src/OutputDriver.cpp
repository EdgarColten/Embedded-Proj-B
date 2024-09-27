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


#define PI 3.1415926535


uint32_t DAC_OUT_SINE_STEP_VALUES[24] = {1365,1489,1613,1737,1861,1985,2110,2234,2358,2482,2606,2730,2854,2978,3103,3227,3351,3475,3599,3723,3847,3971,4096};
uint32_t sineLookupTable[] = {
2048, 2148, 2249, 2349, 2448, 2546, 2643, 2738,
2832, 2924, 3013, 3101, 3186, 3268, 3347, 3423,
3496, 3565, 3631, 3693, 3751, 3805, 3854, 3899,
3940, 3976, 4008, 4035, 4057, 4074, 4086, 4094,
4096, 4094, 4086, 4074, 4057, 4035, 4008, 3976,
3940, 3899, 3854, 3805, 3751, 3693, 3631, 3565,
3496, 3423, 3347, 3268, 3186, 3101, 3013, 2924,
2832, 2738, 2643, 2546, 2448, 2349, 2249, 2148,
2048, 1948, 1847, 1747, 1648, 1550, 1453, 1358,
1264, 1172, 1083, 995, 910, 828, 749, 673,
600, 531, 465, 403, 345, 291, 242, 197,
156, 120, 88, 61, 39, 22, 10, 2,
0, 2, 10, 22, 39, 61, 88, 120,
156, 197, 242, 291, 345, 403, 465, 531,
600, 673, 749, 828, 910, 995, 1083, 1172,
1264, 1358, 1453, 1550, 1648, 1747, 1847, 1948};

OutputDriver::OutputDriver()
{
	HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
	HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);

	freq = 1;
	amp = 3;
	shape = sine;
	step = 0;
	DAC_OUT = 0;
	direction = 0;
}

void OutputDriver::update_Channel1()
{


	HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, DAC_OUT);

	if(DAC_OUT < 4095 && direction == 0)
	{
		DAC_OUT++;
	}

	else if(DAC_OUT >= 4095 && direction == 0)
	{
		direction = 1;
	}


	else if (DAC_OUT <= 4095 && DAC_OUT > 0 && direction == 1)
	{
		DAC_OUT--;
	}

	else if (DAC_OUT <= 4095 && DAC_OUT <= 0 && direction == 1)
	{
		direction = 0;
	}


	return;
}

void OutputDriver::update_Channel2()
{
	HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_2, DAC_ALIGN_12B_R, DAC_OUT);
}

void OutputDriver::setStep(uint32_t val)
{
	step = val;
}
