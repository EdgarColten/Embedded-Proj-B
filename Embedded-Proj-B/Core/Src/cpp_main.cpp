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
//
// GPIO
// PA_1
// PA_3 (D
//
// PB_1 (LD3) =
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
#include "waveQueue.h"

extern "C" void cpp_main(void);


void cpp_main(){
	displayQueue OLED_Queue1;
	displayQueue OLED_Queue2;

	waveQueue waveQueue1;
	waveQueue waveQueue2;

	OutputDriver Channel1 = OutputDriver(1,&waveQueue1,&OLED_Queue1);
	OutputDriver Channel2 = OutputDriver(2,&waveQueue2,&OLED_Queue2);

	//OLED display1 = OLED(1,&OLED_Queue1);
	//OLED display2 = OLED(2,&OLED_Queue2);

	waveProp signal1;
	signal1.amplitude = 4000;
	signal1.frequency = 100;
	signal1.type = square;
	signal1.delay = 0;

	waveProp signal2;
	signal2.amplitude = 1;
	signal2.frequency = 830;
	signal2.type = sine;
	signal2.delay = 3;

	waveQueue1.enqueue(signal1);
	waveQueue2.enqueue(signal2);

	Channel1.update_Channel(Channel1);
	Channel2.update_Channel(Channel1);



	while(1)
	{

	}
}
