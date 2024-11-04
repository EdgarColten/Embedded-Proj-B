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
#include "Semaphore.h"
#include "inputMaster.h"


static Semaphore values;

extern TIM_HandleTypeDef htim7;


extern "C" void myTIM7_IQRHandler(void)
{
	if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))
	{
		if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE))
		{
			__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
			values.enqueue(1);
		}
	}
}

extern "C" void cpp_main();

void cpp_main()
{
//	//NVIC_SystemReset(); //resets system

	inputQueue inputC;

	displayQueue OLED_Queue;

	waveQueue waveQueue;

    inputMaster input = inputMaster(&inputC,&values);

	Channel channel = Channel(&inputC,&waveQueue);

	OutputDriver Signal = OutputDriver(&waveQueue,&OLED_Queue);

	OLED display = OLED(&OLED_Queue);


    while(1)
	{
		input.update();

	    channel.updateChannel();

		Signal.update_Channel();

		display.updateDisplay();
	}
}
