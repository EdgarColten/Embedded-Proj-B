/*
 * cpp_main.cpp
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */
///////////////////////////////////////////////////////////////////
// Hardware Settings:
// DAC1 both channels enabled {PA4 = DAC1_OUT1 and PA5 = DAC1_OUT2}
//
// Current Clock config:
// SysClk = 80 MHz
//
// Current Timer config:
// tim2 enabled
// Prescalar = 4
// Auto Reload = 2731
//
// tim6 enabled
// Prescalar = 4
// Auto Reload = 2731
//
// SPI config:
// PB_7	= DC
// PA_1	= CLK
// PA_3	= RES
// PA_6	= CS
// PA_7	= MOSI

// GPIO Ouput:
// PB_5 = Red LED
// PB_4 = Green LED
//
// GPIO Input:
// PA_12 = Freq knob pin A
// PB_0 = Freq knob pin B
// PB_7 = Amp knob pin A
// PB_6 = Amp knob pin B
// PB_1 = Delay knob pin A
// PA_11 = Delay knob pin B
// PA_10 = Shape Button
// PA_9 = Channel select switch

//
///////////////////////////////////////////////////////////////////


#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

//custom includes
#include "cpp_main.h"
#include "MemoryBuffer.h"
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

	inputQueue inputC;
	MemoryBuffer MBuff1;

	displayQueue OLED_Queue;
	MemoryBuffer MBuff2;

	waveQueue waveQueue;
	MemoryBuffer MBuff3;


    inputMaster input = inputMaster(&inputC,&values);

	Channel channel = Channel(&inputC,&waveQueue);

	OutputDriver Signal = OutputDriver(&waveQueue,&OLED_Queue);

	OLED display = OLED(&OLED_Queue);


    while(1)
	{

    	MBuff1.check_memory();

    	MBuff2.check_memory();

    	MBuff3.check_memory();

		input.update();

	    channel.updateChannel();

		Signal.update_Channel();

		display.updateDisplay();

		GPIOB->ODR ^= (1 << 5);
	}
}
