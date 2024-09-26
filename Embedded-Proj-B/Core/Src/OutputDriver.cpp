/*
 * OutputDriver.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "Queue.h"
#include "OutputDriver.h"

extern DAC_HandleTypeDef hdac1;
uint32_t DAC_OUT_SINE_STEP_VALUES[24] = {1365,1489,1613,1737,1861,1985,2110,2234,2358,2482,2606,2730,2854,2978,3103,3227,3351,3475,3599,3723,3847,3971,4096};

OutputDriver::OutputDriver()
{
	freq = 1;
	amp = 3;
	shape = sine;
}

void OutputDriver::update_Channel1()
{

}
