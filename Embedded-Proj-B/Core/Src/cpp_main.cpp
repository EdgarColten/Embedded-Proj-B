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
// SysClk = 70 MHz
// tim2 enabled
// Prescalar = 0
// Auto Reload = 2731 (100 Hz)
//
///////////////////////////////////////////
#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"
#include "Queue.h"
#include "OutputDriver.h"


extern "C" void cpp_main(void);

extern DAC_HandleTypeDef hdac1;
extern TIM_HandleTypeDef htim2;



void cpp_main(){

	OutputDriver dac;
	//uint32_t DAC_OUT = 0;
	//uint8_t direction = 0;
	//HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);

	//float val = 0;

	//DAC_OUT = val*(4096)/3.3;

	//dac.update_Channel1();

	uint32_t count = 0;

	while(1)
	{
		//HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 2047);

		dac.update_Channel1(100,1);
		//count++;
/*
		if(count == 1000)
		{
			//_HAL_TIM_SET_AUTORELOAD();
			__HAL_TIM_SET_AUTORELOAD(&htim2,250);
		}
*/
		//HAL_Delay(1);


	}
}
