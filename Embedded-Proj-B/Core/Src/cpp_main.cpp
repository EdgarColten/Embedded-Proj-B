/*
 * cpp_main.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */
////////////////////////////////////////////
// Hardware Settings:
// I2C1 enabled {PA9 SCL and PA10 SDA}
// DAC1 both channels enabled {PA4 = DAC1_OUT1 and PA5 = DAC1_OUT2}
//
// Current Clock config:
// SysClk = 30 MHz
// I2C Clk = 30 MHz
//
//
//
///////////////////////////////////////////
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "Queue.h"
#include "OutputDriver.h"


extern "C" void cpp_main(void);

extern DAC_HandleTypeDef hdac1;

void cpp_main(){

	OutputDriver dac;
	//uint32_t DAC_OUT = 0;
	//uint8_t direction = 0;
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);

	//float val = 0;

	//DAC_OUT = val*(4096)/3.3;
	//TIM2->PSC = 3;
	//dac.update_Channel1();
	while(1)
	{
		//HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 2047);

		dac.update_Channel1();

		HAL_Delay(1);


	}
}
