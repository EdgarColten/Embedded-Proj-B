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
//<<<<<<< main
#include "SSD1306_SPI_Driver.h"
//=======
#include "SSD1306_I2C_Driver.h"
#include "channel.h"
//>>>>>>> Colten-Classes
#include "waveQueue.h"
#include "Semaphor.h"


extern "C" void cpp_main(void);
//?
Queue semaphor;

void cpp_main(){


	while(1)
	{
//Test Cases for applicationClass1Colten
		//S1.enqueue from timer interrupt
		//(if not S1 dequeue) task1.update();

	}

}
