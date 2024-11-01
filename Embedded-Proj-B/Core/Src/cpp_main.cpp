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
// GPIO Pins:
// PA_1 =
// PA_3 =
//
// PB_1 =
//
///////////////////////////////////////////////////////////////////


#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

//custom includes
#include "cpp_main.h"
#include "Queue.h"
#include "OutputDriver.h"
#include "SSD1306_SPI_Driver.h"
#include "channel.h"
#include "waveQueue.h"
#include "Semaphor.h"


static Semaphor values;

extern TIM_HandleTypeDef htim7;


   //Worked with Olivia C
extern "C" void myTIM7_IQRHandler(void)
{
	if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) != 0)
		{
			__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
			values.enqueue(1);
		}
	}
}

extern "C" void cpp_main();

void cpp_main()
{
	inputQueue inputC1;
	inputQueue inputC2;

	displayQueue OLED_Queue1;
	displayQueue OLED_Queue2;

	waveQueue waveQueue1;
	waveQueue waveQueue2;

	nextState ns1;
	ns1.sw_select = 0; //channel 1
    ns1.knobA = 0; //amplitude = 0.2
    ns1.knobF = 0; //frequency = 50 Hz
    ns1.knobD = 0; //N/A
    ns1.btn_S = 0; //shape = square
/*
    nextState ns2;
	ns1.sw_select = 2;
	ns1.knobA = 0;
	ns1.knobF = 1;
	ns1.knobD = 1;
	ns1.btn_S = 1;
*/
	Channel channel1 = Channel(&inputC1,&waveQueue1);
	//Channel channel2 = Channel(&inputC2,&waveQueue2);

	OutputDriver signal1 = OutputDriver(1,&waveQueue1,&OLED_Queue1);
	//OutputDriver signal2 = OutputDriver(2,&waveQueue2,&OLED_Queue2);

	OLED display1 = OLED(1,&OLED_Queue1);
	//OLED display2 = OLED(2,&OLED_Queue2);

	inputC1.enqueue(ns1);

	channel1.updateChannel();

	signal1.update_Channel(signal1);
	display1.updateDisplay();

	while(1)
	{

	}

}
