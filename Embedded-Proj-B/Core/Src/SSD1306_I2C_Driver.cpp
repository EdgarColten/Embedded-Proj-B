/*
 * SSD1306_I2C_Driver.cpp
 *
 *  Created on: Sep 21, 2024
 *      Author: LogMa
 */
#include "main.h"
#include <cstdint>

#include "stm32l4xx_hal.h"
#include "SSD1306_I2C_Driver.h"
#include "characters.h"
#include "displayQueue.h"



OLED::OLED(uint8_t chann,displayQueue* q){ // @suppress("Class members should be properly initialized")
	queue = q;
	channel = chann;
	startUpF = false;
	startUpW = false;

	for(int32_t i = 0; i < 6; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			code[i][j] = 0x00;
			//code1[i][j] = 0x00;
			//code2[i][j] = 0x00;
		}
	}

	SSD1306_init();
	set_OLED();
}

void OLED::set_partial_code(uint8_t* value, uint8_t position)
{

	for(int32_t i = 0; i < 16; i++)
	{
		code[position][i] = value[i];
	}
	return;
}

/*
void OLED::set_partial_code2(uint8_t* value, uint8_t position)
{

	for(int32_t i = 0; i < 16; i++)
	{
		code2[position][i] = value[i];
	}
	return;
}
*/

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

	set_column_address(30,37);
	set_page_address(0,1);
	send_data(one);


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
	send_data(C);

	set_column_address(21,28);
	set_page_address(4,5);
	send_data(H);

	set_column_address(30,37);
	set_page_address(4,5);
	send_data(two);

	//page 6 & 7
	set_column_address(12,19);
	set_page_address(6,7);
	send_data(F);

	set_column_address(21,28);
	set_page_address(6,7);
	send_data(R);

	set_column_address(30,37);
	set_page_address(6,7);
	send_data(E);

	set_column_address(39,46);
	set_page_address(6,7);
	send_data(Q);

	set_column_address(50,57);
	set_page_address(6,7);
	send_data(equal);


	return;
}

void OLED::updateChannel_1()
{
	clearChannel_1();

	//value TODO: display the frequency1 value
	set_column_address(61,68);
	set_page_address(2,3);
	send_data(code[0]);

	set_column_address(70,77);
	set_page_address(2,3);
	send_data(code[1]);

	set_column_address(79,86);
	set_page_address(2,3);
	send_data(code[2]);

	set_column_address(88,95);
	set_page_address(2,3);
	send_data(code[3]);



	//shape TODO: display the wave1 type
	set_column_address(112,119);
	set_page_address(2,3);
	send_data(code[4]);

	set_column_address(120,127);
	set_page_address(2,3);
	send_data(code[5]);

	return;
}

void OLED::updateChannel_2()
{
	clearChannel_2();

	//value TODO: display the frequency2 value
	set_column_address(61,68);
	set_page_address(6,7);
	send_data(code[0]);

	set_column_address(70,77);
	set_page_address(6,7);
	send_data(code[1]);

	set_column_address(79,86);
	set_page_address(6,7);
	send_data(code[2]);

	set_column_address(88,95);
	set_page_address(6,7);
	send_data(code[3]);


	//shape TODO: display the wave2 type
	set_column_address(112,119);
	set_page_address(6,7);
	send_data(code[4]);

	set_column_address(120,127);
	set_page_address(6,7);
	send_data(code[5]);

	return;
}

void OLED::updateDisplay()
{
	displayValues dValue;
	bool notEmpty = queue->dequeue(&dValue);

	if(notEmpty == false)
		return;



	if(storedValues.F != dValue.F && startUpF == true) //indicates a new frequency
	{
		storedValues.F = dValue.F;

		waveFreq[0] = (storedValues.F - (storedValues.F%1000)) / 1000;
		waveFreq[1] = (storedValues.F%1000 - storedValues.F%100) /100;
		waveFreq[2] = (((storedValues.F%1000)%100) - (storedValues.F%10)) /10;
		waveFreq[3] = (((storedValues.F%1000)%100)%10);

		switch(waveFreq[0])
		{
			case 0:
			{
				set_partial_code(blank,0);
				break;
			}
			case 1:
			{
				set_partial_code(one,0);
				break;
			}

			default:
			{
				set_partial_code(blank,0);
				break;
			}

		}

		switch(waveFreq[1])
		{
			case 0:
			{
				if(waveFreq[0] == 0)
				{
					set_partial_code(blank,1);
					break;
				}
				else
				{
					set_partial_code(zero,1);
					break;
				}

			}
			case 1:
			{

				set_partial_code(one,1);
				break;
			}
			case 2:
			{

				set_partial_code(two,1);
				break;
			}
			case 3:
			{

				set_partial_code(three,1);
				break;
			}
			case 4:
			{

				set_partial_code(four,1);
				break;
			}
			case 5:
			{

				set_partial_code(five,1);
				break;
			}
			case 6:
			{

				set_partial_code(six,1);
				break;
			}
			case 7:
			{

				set_partial_code(seven,1);
				break;
			}
			case 8:
			{

				set_partial_code(eight,1);
				break;
			}
			case 9:
			{

				set_partial_code(nine,1);
				break;
			}

			default:
			{
				set_partial_code(blank,1);
				break;
			}

		}

		switch(waveFreq[2])
		{
			case 0:
			{
				if(waveFreq[1] == 0 && waveFreq[0] == 0)
				{
					set_partial_code(blank,2);
					break;
				}

				set_partial_code(zero,2);
				break;
			}
			case 1:
			{
				set_partial_code(one,2);
				break;
			}
			case 2:
			{
				set_partial_code(two,2);
				break;
			}
			case 3:
			{
				set_partial_code(three,2);
				break;
			}
			case 4:
			{
				set_partial_code(four,2);
				break;
			}
			case 5:
			{
				set_partial_code(five,2);
				break;
			}
			case 6:
			{
				set_partial_code(six,2);
				break;
			}
			case 7:
			{
				set_partial_code(seven,2);
				break;
			}
			case 8:
			{
				set_partial_code(eight,2);
				break;
			}
			case 9:
			{
				set_partial_code(nine,2);
				break;
			}

			default:
			{
				set_partial_code(blank,2);
				break;
			}

		}


		switch(waveFreq[3])
		{
			case 0:
			{
				set_partial_code(zero,3);
				break;
			}
			case 1:
			{
				set_partial_code(one,3);
				break;
			}
			case 2:
			{
				set_partial_code(two,3);
				break;
			}
			case 3:
			{
				set_partial_code(three,3);
				break;
			}
			case 4:
			{
				set_partial_code(four,3);
				break;
			}
			case 5:
			{
				set_partial_code(five,3);
				break;
			}
			case 6:
			{
				set_partial_code(six,3);
				break;
			}
			case 7:
			{
				set_partial_code(seven,3);
				break;
			}
			case 8:
			{
				set_partial_code(eight,3);
				break;
			}
			case 9:
			{
				set_partial_code(nine,3);
				break;
			}

			default:
			{
				set_partial_code(blank,3);
				break;
			}

		}
		if(channel == 1)
		{
			updateChannel_1();
		}

		if(channel == 2)
		{
			updateChannel_2();
		}
	}

	else if (storedValues.F != dValue.F && startUpF == false)
	{
		storedValues.F = dValue.F;

		waveFreq[0] = (storedValues.F - (storedValues.F%1000)) / 1000;
		waveFreq[1] = (storedValues.F%1000 - storedValues.F%100) /100;
		waveFreq[2] = (((storedValues.F%1000)%100) - (storedValues.F%10)) /10;
		waveFreq[3] = (((storedValues.F%1000)%100)%10);

		switch(waveFreq[0])
		{
			case 0:
			{
				set_partial_code(blank,0);
				break;
			}
			case 1:
			{
				set_partial_code(one,0);
				break;
			}

			default:
			{
				set_partial_code(blank,0);
				break;
			}

		}

		switch(waveFreq[1])
		{
			case 0:
			{
				if(waveFreq[0] == 0)
				{
					set_partial_code(blank,1);
					break;
				}
				else
				{
					set_partial_code(zero,1);
					break;
				}

			}
			case 1:
			{

				set_partial_code(one,1);
				break;
			}
			case 2:
			{

				set_partial_code(two,1);
				break;
			}
			case 3:
			{

				set_partial_code(three,1);
				break;
			}
			case 4:
			{

				set_partial_code(four,1);
				break;
			}
			case 5:
			{

				set_partial_code(five,1);
				break;
			}
			case 6:
			{

				set_partial_code(six,1);
				break;
			}
			case 7:
			{

				set_partial_code(seven,1);
				break;
			}
			case 8:
			{

				set_partial_code(eight,1);
				break;
			}
			case 9:
			{

				set_partial_code(nine,1);
				break;
			}

			default:
			{
				set_partial_code(blank,1);
				break;
			}

		}

		switch(waveFreq[2])
		{
			case 0:
			{
				if(waveFreq[1] == 0 && waveFreq[0] == 0)
				{
					set_partial_code(blank,2);
					break;
				}

				set_partial_code(zero,2);
				break;
			}
			case 1:
			{
				set_partial_code(one,2);
				break;
			}
			case 2:
			{
				set_partial_code(two,2);
				break;
			}
			case 3:
			{
				set_partial_code(three,2);
				break;
			}
			case 4:
			{
				set_partial_code(four,2);
				break;
			}
			case 5:
			{
				set_partial_code(five,2);
				break;
			}
			case 6:
			{
				set_partial_code(six,2);
				break;
			}
			case 7:
			{
				set_partial_code(seven,2);
				break;
			}
			case 8:
			{
				set_partial_code(eight,2);
				break;
			}
			case 9:
			{
				set_partial_code(nine,2);
				break;
			}

			default:
			{
				set_partial_code(blank,2);
				break;
			}

		}


		switch(waveFreq[3])
		{
			case 0:
			{
				set_partial_code(zero,3);
				break;
			}
			case 1:
			{
				set_partial_code(one,3);
				break;
			}
			case 2:
			{
				set_partial_code(two,3);
				break;
			}
			case 3:
			{
				set_partial_code(three,3);
				break;
			}
			case 4:
			{
				set_partial_code(four,3);
				break;
			}
			case 5:
			{
				set_partial_code(five,3);
				break;
			}
			case 6:
			{
				set_partial_code(six,3);
				break;
			}
			case 7:
			{
				set_partial_code(seven,3);
				break;
			}
			case 8:
			{
				set_partial_code(eight,3);
				break;
			}
			case 9:
			{
				set_partial_code(nine,3);
				break;
			}

			default:
			{
				set_partial_code(blank,3);
				break;
			}

		}
		startUpF = true;

		if(channel == 1)
		{
			updateChannel_1();
		}

		if(channel == 2)
		{
			updateChannel_2();
		}

	}


	if(storedValues.type != dValue.type && startUpW == true)
	{
		storedValues.type = dValue.type;
		switch(storedValues.type)
		{
			case sine:
			{
				set_partial_code(SINE1,4);
				set_partial_code(SINE2,5);
				break;
			}
			case square:
			{
				set_partial_code(SQUARE,4);
				set_partial_code(SQUARE,5);
				break;
			}
			case pulse:
			{
				set_partial_code(PULSE,4);
				set_partial_code(PULSE,5);
				break;
			}
			case delay:
			{
				set_partial_code(D,4);
				set_partial_code(D,5);
				break;
			}
			default:
				break;
		}
		if(channel == 1)
		{
			updateChannel_1();
		}

		if(channel == 2)
		{
			updateChannel_2();
		}
	}
	else if(storedValues.type != dValue.type && startUpW == false)
	{

		storedValues.type = dValue.type;
		switch(storedValues.type)
		{
			case sine:
			{
				set_partial_code(SINE1,4);
				set_partial_code(SINE2,5);
				break;
			}
			case square:
			{
				set_partial_code(SQUARE,4);
				set_partial_code(SQUARE,5);
				break;
			}
			case pulse:
			{
				set_partial_code(PULSE,4);
				set_partial_code(PULSE,5);
				break;
			}
			case delay:
			{
				set_partial_code(D,4);
				set_partial_code(D,5);
				break;
			}
			default:
				break;
		}
		startUpW = true;

		if(channel == 1)
		{
			updateChannel_1();
		}

		if(channel == 2)
		{
			updateChannel_2();
		}

	}

	return;

}




void OLED::send_command(uint8_t command)
{
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT,SSD1306_I2C_ADDR,0x00, 1, &command, 1, HAL_MAX_DELAY);
    return;
}

void OLED::send_data(uint8_t* data)
{
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1, data, CHARACTER_SIZE, HAL_MAX_DELAY);
	return;

}

void OLED::SSD1306_init()
{
    send_command(0xAE); //set display off
    send_command(0x20); //Set addressing mode
    send_command(0x00); //horizontal addressing mode

    send_command(0xD3); //Display offset
    send_command(0x00); //no offset

    send_command(0x40); //set display start line

    send_command(0x81);// set contrast
    send_command(0xFF);//max contrast

    send_command(0xA1);//set segment remap, col address SEG0 = 127
    send_command(0xA4);

    send_command(0xA8); //set MUX Ratio
    send_command(0x3F);

    send_command(0xC8); //set com scan mode, C8 = from COM[N - 1] to COM[0]

    send_command(0xDA);  //set COM pins hardware configuration
    send_command(0x12);

    send_command(0xA4); //set output with RAM contents

    send_command(0xD9); //set precharge value
    send_command(0x22);

    send_command(0xD5); //Set frequency (Tentatively)
    send_command(0x80);

    send_command(0xDB);//set vcomh
    send_command(0x20); //0x20,0.77xVcc

    send_command(0x8D);//set DC-DC enable
    send_command(0x14);

    send_command(0xAF); //set display on
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

void OLED::clearChannel_1()
{
	set_column_address(61,68);
	set_page_address(2,3);
	send_data(blank);

	set_column_address(70,77);
	set_page_address(2,3);
	send_data(blank);

	set_column_address(79,86);
	set_page_address(2,3);
	send_data(blank);

	set_column_address(88,95);
	set_page_address(2,3);
	send_data(blank);

	set_column_address(112,119);
	set_page_address(2,3);
	send_data(blank);

	set_column_address(120,127);
	set_page_address(2,3);
	send_data(blank);
	return;
}

void OLED::clearChannel_2()
{
	set_column_address(61,68);
	set_page_address(6,7);
	send_data(blank);

	set_column_address(70,77);
	set_page_address(6,7);
	send_data(blank);

	set_column_address(79,86);
	set_page_address(6,7);
	send_data(blank);

	set_column_address(88,95);
	set_page_address(6,7);
	send_data(blank);

	set_column_address(112,119);
	set_page_address(6,7);
	send_data(blank);

	set_column_address(120,127);
	set_page_address(6,7);
	send_data(blank);

	return;
}
