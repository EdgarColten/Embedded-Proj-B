/*
 * cpp_main.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */
///////////////////////////////////////////////////////////////////
// Hardware Settings:
// I2C1 enabled {PA9 SCL and PA10 SDA}
// DAC1 both channels enabled {PA4 = DAC1_OUT1 and PA5 = DAC1_OUT2}
//
// Current Clock config:
// SysClk = 80 MHz
//
// Current Timer config:
// tim2 enabled
// Prescalar = 0
// Auto Reload = 2731 (100 Hz)
//
// tim6 enabled
// Prescalar = 0
// Auto Reload = 2731 (100 Hz)
//
///////////////////////////////////////////////////////////////////


#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

//custom includes
#include "cpp_main.h"
#include "Queue.h"
#include "OutputDriver.h"
#include "SSD1306_I2C_Driver.h"

extern "C" void cpp_main(void);


void cpp_main(){
	displayQueue OLED_Queue1;
	displayQueue OLED_Queue2;

	OutputDriver Channel1 = OutputDriver(1,&OLED_Queue1);
	OutputDriver Channel2 = OutputDriver(2,&OLED_Queue2);

	OLED display1 = OLED(1,&OLED_Queue1);
	OLED display2 = OLED(2,&OLED_Queue2);

	waveProp signal1;
	signal1.amplitude = 2;
	signal1.frequency = 750;
	signal1.type = sine;
	signal1.delay = 0;

	waveProp signal2;
	signal2.amplitude = 1;
	signal2.frequency = 500;
	signal2.type = square;
	signal2.delay = 0;


	Channel1.update_Channel(signal1, Channel1);
	Channel2.update_Channel(signal2, Channel1);


	uint32_t count_s = 1;
	uint32_t count_2s = (2 * 1);
	uint32_t count_4s = (2 * 1);

	while(1)
	{
/*
		if(!count_s)
		{
			Channel1.update_Channel(signal1, Channel1);
			Channel2.update_Channel(signal2, Channel1);

			display1.updateDisplay();
			display2.updateDisplay();

			count_2s--;
			count_s = 1;
		}

		if(!count_2s)
		{
			if(signal1.frequency > 1000)
				signal1.frequency = 0;
			else
				signal1.frequency++;

			if(signal2.frequency > 1000)
				signal2.frequency = 0;
			else
				signal2.frequency++;

			count_4s--;
			count_2s = (2 * 1);
		}

		if(!count_4s)
		{
			if(signal1.type == pulse)
				signal1.type = sine;

			else if(signal1.type == sine)
				signal1.type = square;

			else if(signal1.type == square)
				signal1.type = pulse;

			if(signal2.type == pulse)
				signal2.type = sine;

			else if(signal2.type == sine)
				signal2.type = square;

			else if(signal2.type == square)
				signal2.type = pulse;

			count_4s = (2 * 1);
		}
		count_s--;
*/
	}
}
