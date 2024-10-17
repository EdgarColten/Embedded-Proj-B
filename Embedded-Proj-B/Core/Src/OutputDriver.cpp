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
#include "stm32l4xx_hal_dac.h"

//custom includes
#include "cpp_main.h"
#include "Queue.h"
#include "OutputDriver.h"
#include "SSD1306_I2C_Driver.h"
#include "displayQueue.h"
#include "Queue.h"


extern DAC_HandleTypeDef hdac1;
//extern DMA_HandleTypeDef hdma_dac_ch1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;


//NOTE: 3.3v = 4095
//NOTE: 1v = 1215
//NOTE: 272 = 1 kHz
//NOTE: 2731 = 100 Hz

//TESTING FOR cpp_main();
/*
	displayQueue OLED_Queue1;
	displayQueue OLED_Queue2;

	waveProp signal1;
	signal1.amplitude = 2;
	signal1.frequency = 500;
	signal1.type = sine;
	signal1.delay = 0;

	waveProp signal2;
	signal2.amplitude = 1;
	signal2.frequency = 1000;
	signal2.type = delay;
	signal2.delay = 3;


	OutputDriver Channel1 = OutputDriver(1,&OLED_Queue1);
	OutputDriver Channel2 = OutputDriver(2,&OLED_Queue2);


	Channel1.update_Channel(signal1, Channel1);
	Channel2.update_Channel(signal2, Channel1);


*/


OutputDriver::OutputDriver(uint8_t chan,displayQueue* q) // @suppress("Class members should be properly initialized")
{
	queue = q;
	freq = 1;
	amp = 1;
	shape = sine;
	autoReload = 2731;
	channel = chan;

	//update_Channel(freq,amp,shape);	//Generation check objects
	updateSine = false;
	updateSquare = false;
	updatePulse = false;
	updateDelay = false;
}


//setting the Auto Reload value
void OutputDriver::setAutoReload(TIM_HandleTypeDef* timmer)
{
    (timmer)->Instance->ARR = (autoReload);
    (timmer)->Init.Period = (autoReload);
	return;
}

void OutputDriver::setAttributes(waveProp signal)
{
	shape = signal.type;
	freq = signal.frequency;
	amp = signal.amplitude;

	return;
}

void OutputDriver::calculateAutoReload()//Period of the signal
{
	uint32_t trig = 0;
	trig = freq * (SIZE);
	autoReload = ((CPU_CLK/trig) - 1); //TODO:find a way to avoid division
	return;
}

void OutputDriver::getAttributes(waveProp* dataPoll)
{
	dataPoll->amplitude = amp;
	dataPoll->frequency = freq;
	dataPoll->type = shape;

	return;
}


void OutputDriver::update_Channel(waveProp signal, OutputDriver channel1) //TODO: take a struct opposed to individual values
{
	if(channel == 1)
	{

		if(signal.type == sine && updateSine == false) //This is the initial time that the sine wave generator is called thus all calcs are needed
		{
		//	shape = sine;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;
			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 1;
			queue->enqueue(dValues);
			updateSine = true;
		}
		else if(signal.type == sine && updateSine == true) //This condition can avoid the calcs if the information hasn't changed thus taking less time to return
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = sine;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();

				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				setAutoReload(&htim2);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 1;
				queue->enqueue(dValues);

			}
		}

		else if(signal.type == square && updateSquare == false)
		{
		//	shape = square;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim2);

			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 1;
			queue->enqueue(dValues);
			updateSquare = true;

		}
		else if(signal.type == square && updateSquare == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = square;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();


				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim2);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 1;
				queue->enqueue(dValues);
				queue->enqueue(dValues);

			}
		}

		else if(signal.type == pulse && updatePulse == false)
		{
		//	shape = pulse;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim2);
			generateWave();

			HAL_TIM_Base_Start(&htim2);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 1;
			queue->enqueue(dValues);
			updatePulse = true;

		}
		else if(signal.type == pulse && updatePulse == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = pulse;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();

				HAL_TIM_Base_Start(&htim2);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				setAutoReload(&htim2);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 1;
				queue->enqueue(dValues);
			}
		}

		return;
	}
	else if(channel == 2)
	{
		if(signal.type == sine && updateSine == false)
		{
		//	shape = sine;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 2;
			queue->enqueue(dValues);
			updateSine = true;
		}
		else if(signal.type == sine && updateSine == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = sine;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 2;
				queue->enqueue(dValues);
			}
		}

		else if(signal.type == square && updateSquare == false)
		{
		//	shape = square;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 2;
			queue->enqueue(dValues);
			updateSquare = true;

		}
		else if(signal.type == square && updateSquare == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = square;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 2;
				queue->enqueue(dValues);
			}
		}

		else if(signal.type == pulse && updatePulse == false)
		{
		//	shape = pulse;
		//	freq = signal.frequency;
		//	amp = signal.amplitude;

			setAttributes(signal);
			calculateAutoReload();

			setAutoReload(&htim6);
			generateWave();

			HAL_TIM_Base_Start(&htim6);
			HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

			dValues.F = freq;
			dValues.type = shape;
			dValues.channel = 2;
			queue->enqueue(dValues);
			updatePulse = true;

		}
		else if(signal.type == pulse && updatePulse == true)
		{
			if(signal.frequency != freq || signal.amplitude != amp)
			{
			//	shape = pulse;
			//	freq = signal.frequency;
			//	amp = signal.amplitude;

				setAttributes(signal);
				calculateAutoReload();

				HAL_TIM_Base_Start(&htim6);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

				setAutoReload(&htim6);
				generateWave();

				dValues.F = freq;
				dValues.type = shape;
				dValues.channel = 2;
				queue->enqueue(dValues);

			}
		}

		else if(signal.type == delay)
		{
			waveProp data; //local
			channel1.getAttributes(&data);
			setAttributes(data);

			calculateAutoReload();
			setAutoReload(&htim6);
			generateWave();

			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
			HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);

			HAL_TIM_Base_Start(&htim6);
			HAL_TIM_Base_Start(&htim2);

			if(signal.delay == 0)
			{
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
			}
			else if(signal.delay > 0 && signal.delay < 8)
			{
				delaySet(signal.delay);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
				HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, delayOutWave, SIZE, DAC_ALIGN_12B_R);

			}

/*
			switch(data.type)
			{
				case sine:
				{
					shape = sine;
					setAttributes(data);
					calculateAutoReload();
					//interruptARR = ((signal.delay/8)*autoReload);

					setAutoReload(&htim6);

					//The plan is to delay the start of htim6 so that I can offset the channel two output.
					//I'll start by testing the sine wave then move onto the others
					//Still need to test this code
//					interruptARR = ((delay/8)*autoReload);

					generateWave();

					if(interruptARR == 0)
					{
						HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
						HAL_TIM_Base_Start(&htim6);
						HAL_TIM_Base_Start(&htim2);
						HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);
						HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

					}

					else
					{
						HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_1);
						//HAL_TIM_Base_Start(&htim2);
						HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, outWave, SIZE, DAC_ALIGN_12B_R);

						HAL_DAC_Stop_DMA(&hdac1, DAC1_CHANNEL_2);
						HAL_TIM_Base_Stop(&htim6);



						//HAL_TIM_Base_Start(&htim16);

						//HAL_TIM_Base_Start(&htim6);
						HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);
					}




					dValues.F = freq;
					dValues.type = shape;
					dValues.channel = 2;
					queue->enqueue(dValues);
					return;
					break;
				}

				case square:
				{
					shape = square;
					setAttributes(data);
					calculateAutoReload();
					setAutoReload(&htim6);


					generateWave();

					HAL_TIM_Base_Start(&htim6);
					HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);

					dValues.F = freq;
					dValues.type = shape;
					dValues.channel = 2;
					queue->enqueue(dValues);
					return;
					break;
				}

				case pulse:
				{
					shape = pulse;
					setAttributes(data);
					calculateAutoReload();
					setAutoReload(&htim6);

					generateWave();

					HAL_TIM_Base_Start(&htim6);
					HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_2, outWave, SIZE, DAC_ALIGN_12B_R);


					dValues.F = freq;
					dValues.type = shape;
					dValues.channel = 2;
					queue->enqueue(dValues);
					return;
					break;
				}

				default:
					break;
			}
*/
		}
		dValues.F = freq;
		dValues.type = shape;
		dValues.channel = 2;
		queue->enqueue(dValues);
		return;
	}
	dValues.F = freq;
	dValues.type = shape;
	dValues.channel = 2;
	queue->enqueue(dValues);
	return;

}

void OutputDriver::delaySet(uint8_t delayValue)
{
	uint32_t shift = delayValue * PHASE_SHIFT;
	Queue shiftedWave;

	for(uint32_t i = 0; i < SIZE; i++)
	{
		shiftedWave.enqueue(outWave[i]);
	}

	for(uint32_t i = 0; i < shift; i++)
	{
		uint32_t hold = 0;
		shiftedWave.dequeue(&hold);
		shiftedWave.enqueue(hold);
	}

	for(uint32_t i = 0; i < SIZE; i++)
	{
		//uint32_t holdNewValue = 0;
		shiftedWave.dequeue(&delayOutWave[i]);
	}
/*
	switch(signal.delay)
	{
		case 0:
		{

			break;
		}

		case 1:
		{

			break;
		}

		case 2:
		{

			break;
		}

		case 3:
		{

			break;
		}

		case 4:
		{

			break;
		}

		case 5:
		{

			break;
		}

		case 6:
		{

			break;
		}

		case 7:
		{
			break;
		}

		default:
			break;

	}
	*/
	return;
}

//Wave generation

void OutputDriver::generateWave()
{
	if(shape == sine)
	{
		uint32_t amplifier = amp * 1220; //1215 = 1V
		for(uint32_t i = 0; i < SIZE; i++)
		{
			outWave[i] =  ((sin(i*(2*PI)/SIZE) + 1) * (amplifier/2)); //TODO:find a way to avoid division
		}
		return;
	}

	else if(shape == square)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			if(i < SIZE/2) //TODO:find a way to avoid division
			{
				outWave[i] = 0;
			}
			else
			{
				outWave[i] = amp * 1215; //1215 = 1 volt
				if(outWave[i] > (MAX_SIZE - 1))
				{
					outWave[i] = (MAX_SIZE - 1);
				}
			}

		}

		return;
	}

	else if(shape == pulse)
	{
		for(uint32_t i = 0; i < SIZE; i++)
		{
			if((i%10) == 0 && i != 0) //TODO:find a way to avoid division
			{
				outWave[i] = amp * 1215; //1215 = 1 volt
			}
			else
				outWave[i] = 0;
		}

		return;
	}

}

