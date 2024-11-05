/*
 * SSD1306_SPI_Driver.cpp
 *
 *  Created on: Oct 28, 2024
 *      Author: LogMa
 */


#include "main.h"
#include <cstdint>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_spi.h"

//custom includes
#include "SSD1306_SPI_Driver.h"
#include "characters.h"
#include "displayQueue.h"


OLED::OLED(displayQueue* dQ){ // @suppress("Class members should be properly initialized")
	queue = dQ;
	channel = 1;
	SPI_CS_count = 0;
	SPI_RST_Count = 0;


	for(int32_t i = 0; i < 6; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			code[i][j] = 0x00;

		}
	}


	SSD1306_init();
	set_OLED();


	updateChannel_1();
	//updateChannel_2();


}

void OLED::set_partial_code(uint8_t* reading,uint8_t* value)
{

	for(int32_t i = 0; i < 16; i++)
	{
		reading[i] = value[i];
	}
	return;
}

void OLED::set_OLED()
{
	clear_display();

	//page 0 & 1
	set_column_address(12,19);
	set_page_address(0,1);
	send_data(C);

	set_column_address(21,28);
	set_page_address(0,1);
	send_data(H);

	//so that this value can change
	set_column_address(30,37);
	set_page_address(0,1);

	if(channel == 1)
		send_data(one);
	else if(channel == 2)
		send_data(two);

	assert((channel == 1) || (channel == 2));
	//page 2 & 3
	set_column_address(12,19);
	set_page_address(2,3);
	send_data(F);

	set_column_address(21,28);
	set_page_address(2,3);
	send_data(R);

	set_column_address(30,37);
	set_page_address(2,3);
	send_data(E);

	set_column_address(39,46);
	set_page_address(2,3);
	send_data(Q);

	set_column_address(50,57);
	set_page_address(2,3);
	send_data(equal);

	//page 4 & 5
	set_column_address(12,19);
	set_page_address(4,5);
	send_data(A);

	set_column_address(21,28);
	set_page_address(4,5);
	send_data(M);

	set_column_address(31,38);
	set_page_address(4,5);
	send_data(P);

	set_column_address(50,57);
	set_page_address(4,5);
	send_data(equal);

	//page 6 & 7
	set_column_address(12,19);
	set_page_address(6,7);
	send_data(S);

	set_column_address(21,28);
	set_page_address(6,7);
	send_data(H);

	set_column_address(30,37);
	set_page_address(6,7);
	send_data(A);

	set_column_address(39,46);
	set_page_address(6,7);
	send_data(P);

	set_column_address(48,55);
	set_page_address(6,7);
	send_data(E);

	return;
}

void OLED::updateChannel_1()
{
	assert(1 == 1);

	//Current Channel display
	set_column_address(30,37);
	set_page_address(0,1);
	send_data(one);

	//Frequency display
	set_column_address(61,68);
	set_page_address(2,3);
	send_data(frequency1[0]);

	set_column_address(70,77);
	set_page_address(2,3);
	send_data(frequency1[1]);

	set_column_address(79,86);
	set_page_address(2,3);
	send_data(frequency1[2]);

	set_column_address(88,95);
	set_page_address(2,3);
	send_data(frequency1[3]);

	//Amplitude Display
	set_column_address(61,68);
	set_page_address(4,5);
	send_data(amplitude1[0]);

	set_column_address(70,77);
	set_page_address(4,5);
	send_data(amplitude1[1]);

	set_column_address(79,86);
	set_page_address(4,5);
	send_data(amplitude1[2]);

	//Wave display
	set_column_address(70,77);
	set_page_address(6,7);
	send_data(shape1[0]);

	set_column_address(78,85);
	set_page_address(6,7);
	send_data(shape1[1]);


	return;
}
void OLED::updateChannel_2()
{

	assert(1 == 1);

	//Current Channel display
	set_column_address(30,37);
	set_page_address(0,1);
	send_data(two);

	//Frequency display
	set_column_address(61,68);
	set_page_address(2,3);
	send_data(frequency2[0]);

	set_column_address(70,77);
	set_page_address(2,3);
	send_data(frequency2[1]);

	set_column_address(79,86);
	set_page_address(2,3);
	send_data(frequency2[2]);

	set_column_address(88,95);
	set_page_address(2,3);
	send_data(frequency2[3]);

	//Amplitude Display
	set_column_address(61,68);
	set_page_address(4,5);
	send_data(amplitude2[0]);

	set_column_address(70,77);
	set_page_address(4,5);
	send_data(amplitude2[1]);

	set_column_address(79,86);
	set_page_address(4,5);
	send_data(amplitude2[2]);

	//Wave display
	set_column_address(70,77);
	set_page_address(6,7);
	send_data(shape2[0]);

	set_column_address(78,85);
	set_page_address(6,7);
	send_data(shape2[1]);

	return;
}

void OLED::updateDisplay()
{
	displayValues dValue;
	bool notEmpty = queue->dequeue(&dValue);

	if(notEmpty == false)
		return;

	assert(notEmpty == true || notEmpty == false);

	channel = dValue.channel;

	if((storedValues.F1 != dValue.F1) || (storedValues.F2 != dValue.F2))
	{
		if((storedValues.F1 != dValue.F1))
		{
			storedValues.F1 = dValue.F1;

			waveFreq[0] = (storedValues.F1 - (storedValues.F1%1000)) / 1000;
			waveFreq[1] = (storedValues.F1%1000 - storedValues.F1%100) /100;
			waveFreq[2] = (((storedValues.F1%1000)%100) - (storedValues.F1%10)) /10;
			waveFreq[3] = (((storedValues.F1%1000)%100)%10);



			switch(waveFreq[0])
			{
				case 0:
				{
					set_partial_code(frequency1[0],blank);
					break;
				}
				case 1:
				{
					set_partial_code(frequency1[0],one);
					break;
				}

				default:
				{
					set_partial_code(frequency1[0],blank);
					break;
				}

			}

			switch(waveFreq[1])
			{
				case 0:
				{
					if(waveFreq[0] == 0)
					{
						set_partial_code(frequency1[1],blank);
						break;
					}
					else
					{
						set_partial_code(frequency1[1],zero);
						break;
					}

				}
				case 1:
				{
					set_partial_code(frequency1[1],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency1[1],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency1[1],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency1[1],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency1[1],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency1[1],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency1[1],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency1[1],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency1[1],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency1[1],blank);
					break;
				}

			}

			switch(waveFreq[2])
			{
				case 0:
				{
					if(waveFreq[1] == 0 && waveFreq[0] == 0)
					{
						set_partial_code(frequency1[2],blank);
						break;
					}

					set_partial_code(frequency1[2],zero);
					break;
				}
				case 1:
				{
					set_partial_code(frequency1[2],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency1[2],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency1[2],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency1[2],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency1[2],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency1[2],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency1[2],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency1[2],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency1[2],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency1[2],blank);
					break;
				}

			}


			switch(waveFreq[3])
			{
				case 0:
				{
					set_partial_code(frequency1[3],zero);
					break;
				}
				case 1:
				{
					set_partial_code(frequency1[3],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency1[3],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency1[3],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency1[3],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency1[3],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency1[3],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency1[3],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency1[3],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency1[3],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency1[3],blank);
					break;
				}

			}

		}

		if((storedValues.F2 != dValue.F2))
		{
			storedValues.F2 = dValue.F2;

			waveFreq[0] = (storedValues.F2 - (storedValues.F2%1000)) / 1000;
			waveFreq[1] = (storedValues.F2%1000 - storedValues.F2%100) /100;
			waveFreq[2] = (((storedValues.F2%1000)%100) - (storedValues.F2%10)) /10;
			waveFreq[3] = (((storedValues.F2%1000)%100)%10);



			switch(waveFreq[0])
			{
				case 0:
				{
					set_partial_code(frequency2[0],blank);
					break;
				}
				case 1:
				{
					set_partial_code(frequency2[0],one);
					break;
				}

				default:
				{
					set_partial_code(frequency2[0],blank);
					break;
				}
			}

			switch(waveFreq[1])
			{
				case 0:
				{
					if(waveFreq[0] == 0)
					{
						set_partial_code(frequency2[1],blank);
						break;
					}
					else
					{
						set_partial_code(frequency2[1],zero);
						break;
					}

				}
				case 1:
				{
					set_partial_code(frequency2[1],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency2[1],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency2[1],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency2[1],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency2[1],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency2[1],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency2[1],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency2[1],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency2[1],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency2[1],blank);
					break;
				}

			}

			switch(waveFreq[2])
			{
				case 0:
				{
					if(waveFreq[1] == 0 && waveFreq[0] == 0)
					{
						set_partial_code(frequency2[2],blank);
						break;
					}

					set_partial_code(frequency2[2],zero);
					break;
				}
				case 1:
				{
					set_partial_code(frequency2[2],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency2[2],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency2[2],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency2[2],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency2[2],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency2[2],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency2[2],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency2[2],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency2[2],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency2[2],blank);
					break;
				}

			}


			switch(waveFreq[3])
			{
				case 0:
				{
					set_partial_code(frequency2[3],zero);
					break;
				}
				case 1:
				{
					set_partial_code(frequency2[3],one);
					break;
				}
				case 2:
				{
					set_partial_code(frequency2[3],two);
					break;
				}
				case 3:
				{
					set_partial_code(frequency2[3],three);
					break;
				}
				case 4:
				{
					set_partial_code(frequency2[3],four);
					break;
				}
				case 5:
				{
					set_partial_code(frequency2[3],five);
					break;
				}
				case 6:
				{
					set_partial_code(frequency2[3],six);
					break;
				}
				case 7:
				{
					set_partial_code(frequency2[3],seven);
					break;
				}
				case 8:
				{
					set_partial_code(frequency2[3],eight);
					break;
				}
				case 9:
				{
					set_partial_code(frequency2[3],nine);
					break;
				}

				default:
				{
					set_partial_code(frequency2[3],blank);
					break;
				}

			}

		}
	}

	if((storedValues.A1 != dValue.A1) || (storedValues.A2 != dValue.A2))
	{
		if((storedValues.A1 != dValue.A1))
		{
			uint32_t tempAmp = 0;
			storedValues.A1 = dValue.A1;

			tempAmp = (storedValues.A1 * 10)/1240;

			waveAmp[0] = (tempAmp - (tempAmp%10)) / 10;
			waveAmp[1] = (tempAmp%10);


			set_partial_code(amplitude1[1],decimal);
			switch(waveAmp[0])
			{
				case 0:
				{
					set_partial_code(amplitude1[0],zero);
					break;
				}

				case 1:
				{
					set_partial_code(amplitude1[0],one);
					break;
				}

				case 2:
				{
					set_partial_code(amplitude1[0],two);
					break;
				}

				case 3:
				{
					set_partial_code(amplitude1[0],three);
					break;
				}

				default:
				{
					set_partial_code(amplitude1[0],zero);
					break;

				}
			}

			switch(waveAmp[1])
			{

				case 0:
				{
					set_partial_code(amplitude1[2],zero);
					break;
				}

				case 1:
				{
					set_partial_code(amplitude1[2],one);
					break;
				}

				case 2:
				{
					set_partial_code(amplitude1[2],two);
					break;
				}

				case 3:
				{
					set_partial_code(amplitude1[2],three);
					break;
				}

				case 4:
				{
					set_partial_code(amplitude1[2],four);
					break;
				}

				case 5:
				{
					set_partial_code(amplitude1[2],five);
					break;
				}

				case 6:
				{
					set_partial_code(amplitude1[2],six);
					break;
				}

				case 7:
				{
					set_partial_code(amplitude1[2],seven);
					break;
				}

				case 8:
				{
					set_partial_code(amplitude1[2],eight);
					break;
				}

				case 9:
				{
					set_partial_code(amplitude1[2],nine);
					break;
				}

				default:
				{
					set_partial_code(amplitude1[2],zero);
					break;

				}
			}
		}

		if((storedValues.A2 != dValue.A2))
		{
			uint32_t tempAmp = 0;
			storedValues.A2 = dValue.A2;

			tempAmp = (storedValues.A2 * 10)/1240;

			waveAmp[0] = (tempAmp - (tempAmp%10)) / 10;
			waveAmp[1] = (tempAmp%10);

			set_partial_code(amplitude2[1],decimal);

			switch(waveAmp[0])
			{
				case 0:
				{
					set_partial_code(amplitude2[0],zero);
					break;
				}

				case 1:
				{
					set_partial_code(amplitude2[0],one);
					break;
				}

				case 2:
				{
					set_partial_code(amplitude2[0],two);
					break;
				}

				case 3:
				{
					set_partial_code(amplitude2[0],three);
					break;
				}

				default:
				{
					set_partial_code(amplitude2[0],zero);
					break;

				}
			}

			switch(waveAmp[1])
			{

				case 0:
				{
					set_partial_code(amplitude2[2],zero);
					break;
				}

				case 1:
				{
					set_partial_code(amplitude2[2],one);
					break;
				}

				case 2:
				{
					set_partial_code(amplitude2[2],two);
					break;
				}

				case 3:
				{
					set_partial_code(amplitude2[2],three);
					break;
				}

				case 4:
				{
					set_partial_code(amplitude2[2],four);
					break;
				}

				case 5:
				{
					set_partial_code(amplitude2[2],five);
					break;
				}

				case 6:
				{
					set_partial_code(amplitude2[2],six);
					break;
				}

				case 7:
				{
					set_partial_code(amplitude2[2],seven);
					break;
				}

				case 8:
				{
					set_partial_code(amplitude2[2],eight);
					break;
				}

				case 9:
				{
					set_partial_code(amplitude2[2],nine);
					break;
				}

				default:
				{
					set_partial_code(amplitude2[2],zero);
					break;

				}
			}
		}

	}

	if(((storedValues.type1 != dValue.type1) || (storedValues.type2 != dValue.type2) || (storedValues.offset != dValue.offset)))
	{

		if(storedValues.type1 != dValue.type1)
		{
			storedValues.type1 = dValue.type1;
			switch(storedValues.type1)
			{
				case sine:
				{
					set_partial_code(shape1[0],SINE1);
					set_partial_code(shape1[1],SINE2);
					break;
				}
				case square:
				{
					set_partial_code(shape1[0],SQUARE);
					set_partial_code(shape1[1],SQUARE);
					break;
				}
				case pulse:
				{
					set_partial_code(shape1[0],PULSE);
					set_partial_code(shape1[1],PULSE);
					break;
				}
				default:
					break;
			}
		}

		if((storedValues.type2 != dValue.type2) || (storedValues.offset != dValue.offset))
		{

			storedValues.type2 = dValue.type2;
			storedValues.offset = dValue.offset;
			switch(storedValues.type2)
			{
				case sine:
				{
					set_partial_code(shape2[0],SINE1);
					set_partial_code(shape2[1],SINE2);
					break;
				}
				case square:
				{
					set_partial_code(shape2[0],SQUARE);
					set_partial_code(shape2[1],SQUARE);
					break;
				}
				case pulse:
				{
					set_partial_code(shape2[0],PULSE);
					set_partial_code(shape2[1],PULSE);
					break;
				}
				case delay:
				{
					set_partial_code(shape2[0],D);
					switch(storedValues.offset)
					{
						case 0:
							set_partial_code(shape2[1],zero);
							break;
						case 1:
							set_partial_code(shape2[1],one);
							break;
						case 2:
							set_partial_code(shape2[1],two);
							break;
						case 3:
							set_partial_code(shape2[1],three);
							break;
						case 4:
							set_partial_code(shape2[1],four);
							break;
						case 5:
							set_partial_code(shape2[1],five);
							break;
						case 6:
							set_partial_code(shape2[1],six);
							break;
						case 7:
							set_partial_code(shape2[1],seven);
							break;
						default:
							set_partial_code(shape2[1],blank);
							break;
					}
					break;
				}
				default:
					break;
			}
		}


	}
	if(channel == 1)
	{
		updateChannel_1();
		return;
	}

	if(channel == 2)
	{
		updateChannel_2();
		return;
	}
}


void OLED::send_command(uint8_t command)
{
	LL_GPIO_ResetOutputPin(SSD1306_DC_GPIO_Port, SSD1306_DC_Pin);
	LL_SPI_TransmitData8(SPI1, command);
	for(uint32_t i = 0; i < MAXDELAY; i++)
			if(LL_SPI_IsActiveFlag_TXE(SPI1))
				break;
	return;
}

void OLED::send_data(uint8_t* data)
{
	LL_GPIO_SetOutputPin(SSD1306_DC_GPIO_Port, SSD1306_DC_Pin);

	for(uint32_t i = 0; i < CHARACTER_SIZE; i++)
	{
		LL_SPI_TransmitData8(SPI1, data[i]);
		for(uint32_t i = 0; i < MAXDELAY; i++)
				if(LL_SPI_IsActiveFlag_TXE(SPI1))
					break;
	}
	return;

}

void OLED::SSD1306_init()
{
	LL_SPI_Enable(SPI1);
	if(SPI_RST_Count == 0)
	{
		LL_GPIO_SetOutputPin(SPI_RST_GPIO_Port, SPI_RST_Pin);
		SPI_RST_Count = 1;
	}

	if(SPI_CS_count == 0)
	{
		LL_GPIO_ResetOutputPin(SPI_CS_GPIO_Port, SPI_CS_Pin);
		SPI_CS_count = 1;
	}

	assert(SPI_CS_count == 1);

    send_command(SSD1306_COMMAND_DISPLAY_OFF); //set display off

    send_command(SSD1306_COMMAND_ADDRESSING_MODE); //Set addressing mode
    send_command(0x00); //horizontal addressing mode

    send_command(SSD1306_COMMAND_SET_OFFSET); //Display offset
    send_command(0x00); //no offset

    send_command(SSD1306_COMMAND_START_LINE); //set display start line

    send_command(SSD1306_COMMAND_CONTRAST_CONTROL);// set contrast
    send_command(0xFF);//max contrast

    send_command(SSD1306_COMMAND_SEG_INVERSE);//set segment remap, col address SEG0 = 127
    send_command(0xA4);

    send_command(SSD1306_COMMAND_SET_MUX); //set MUX Ratio
    send_command(0x3F);

    send_command(SSD1306_COMMAND_COM_SCAN_INVERSE); //set com scan mode, C8 = from COM[N - 1] to COM[0]

    send_command(SSD1306_COMMAND_SET_COM_Hardware);  //set COM pins hardware configuration
    send_command(0x12);

    send_command(0xA4); //set output with RAM contents TODO make a define

    send_command(SSD1306_COMMAND_SET_PRECHARGE_PERIOD); //set precharge value
    send_command(0x22);

    send_command(SSD1306_COMMAND_CLOCK_DIIVDER); //Set frequency (Tentatively)
    send_command(0x80);

    send_command(SSD1306_COMMAND_VCOMH_DSEL_LEVEL);//set vcomh
    send_command(0x20); //0x20,0.77xVcc

    send_command(SSD1306_COMMAND_SET_DC_DC_ENABLE);//set DC-DC enable
    send_command(0x14);

    send_command(SSD1306_COMMAND_DISPLAY_ON); //set display on
    clear_display();
    return;
}

void OLED::set_column_address(uint8_t begin, uint8_t end)
{
    //Horizontal addressing mode (ONE I'LL USE)
    send_command(SSD1306_SET_COLUMN_ADDR); //set Column address (make a function for this)
    send_command(begin); //column address/position start
    send_command(end); //column address/position end
    return;
}

void OLED::set_page_address(uint8_t begin, uint8_t end)
{
    //Horizontal addressing mode (ONE I'LL USE)
    send_command(SSD1306_SET_PAGE_ADDR); //set Column address (make a function for this)
    send_command(begin); //column address/position start
    send_command(end); //column address/position end
    return;
}

void OLED::clear_display()
{
	set_column_address(0,127);
	set_page_address(0,7);

	uint8_t clear[8][128] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	assert(clear[0][0] == 0);

	for(int32_t i = 0; i < 8; i++)
	{
		//For one page
		for(int32_t j = 0; j < 8; j++)
		{
			send_data(clear[j]);
		}

	}
	return;
}
