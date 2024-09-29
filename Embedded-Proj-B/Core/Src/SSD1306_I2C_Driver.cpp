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



OLED::OLED(){
	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			code1[i][j] = 0x00;
			code2[i][j] = 0x00;
			code3[i][j] = 0x00;
			code4[i][j] = 0x00;
		}
	}

}

void OLED::set_partial_code1(uint8_t* value, uint8_t position)
{

	for(int32_t i = 0; i < 16; i++)
	{
		code1[position][i] = value[i];
	}
	return;
}
void OLED::set_code1(uint8_t* upperAddress, uint8_t* lowerAddress, uint8_t* upperData, uint8_t* lowerData)
{
	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(i == 0)
				code1[i][j] = upperAddress[j];
			else if(i == 1)
				code1[i][j] = lowerAddress[j];
            else if(i == 2)
				code1[i][j] = upperData[j];
			else if(i == 3)
				code1[i][j] = lowerData[j];
		}
	}
}
void OLED::set_code2(uint8_t* upperAddress, uint8_t* lowerAddress, uint8_t* upperData, uint8_t* lowerData)
{
	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(i == 0)
				code2[i][j] = upperAddress[j];
			else if(i == 1)
				code2[i][j] = lowerAddress[j];
            else if(i == 2)
				code2[i][j] = upperData[j];
			else if(i == 3)
				code2[i][j] = lowerData[j];
		}
	}
}
void OLED::set_code3(uint8_t* upperAddress, uint8_t* lowerAddress, uint8_t* upperData, uint8_t* lowerData)
{
	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(i == 0)
				code3[i][j] = upperAddress[j];
			else if(i == 1)
				code3[i][j] = lowerAddress[j];
            else if(i == 2)
				code3[i][j] = upperData[j];
			else if(i == 3)
				code3[i][j] = lowerData[j];
		}
	}
}
void OLED::set_code4(uint8_t* upperAddress, uint8_t* lowerAddress, uint8_t* upperData, uint8_t* lowerData)
{
	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(i == 0)
				code4[i][j] = upperAddress[j];
			else if(i == 1)
				code4[i][j] = lowerAddress[j];
            else if(i == 2)
				code4[i][j] = upperData[j];
			else if(i == 3)
				code4[i][j] = lowerData[j];
		}
	}
}

bool OLED::isBlank1()
{

	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(code1[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool OLED::isBlank2()
{

	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(code2[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool OLED::isBlank3()
{

	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(code3[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}
bool OLED::isBlank4()
{

	for(int32_t i = 0; i < 4; i++)
	{
		for(int32_t j = 0; j < 16; j++)
		{
			if(code4[i][j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

void OLED::set_OLED()
{
	clear_display();

	//page 0 & 1
	if(isBlank1() == false)
	{
		set_column_address(12,19);
		set_page_address(0,1);
		send_data(zero);

		set_column_address(21,28);
		set_page_address(0,1);
		send_data(x);

        set_column_address(58,65);
		set_page_address(0,1);
		send_data(vertLine);

        set_column_address(76,83);
		set_page_address(0,1);
		send_data(zero);

		set_column_address(85,92);
		set_page_address(0,1);
		send_data(x);
	}

	else
	{
		set_column_address(12,19);
		set_page_address(0,1);
		send_data(blank);

		set_column_address(21,28);
		set_page_address(0,1);
		send_data(blank);

        set_column_address(58,65);
		set_page_address(0,1);
		send_data(blank);

        set_column_address(76,83);
		set_page_address(0,1);
		send_data(blank);

		set_column_address(85,92);
		set_page_address(0,1);
		send_data(blank);
	}

    //Address
	set_column_address(30,37);
	set_page_address(0,1);
	send_data(code1[0]);

	set_column_address(39,46);
	set_page_address(0,1);
	send_data(code1[1]);

    //Data
	set_column_address(94,101);
	set_page_address(0,1);
	send_data(code1[2]);

	set_column_address(103,110);
	set_page_address(0,1);
	send_data(code1[3]);

	//page 2 & 3
	if(isBlank2() == false)
	{
		set_column_address(12,19);
		set_page_address(2,3);
		send_data(zero);

		set_column_address(21,28);
		set_page_address(2,3);
		send_data(x);

        set_column_address(58,65);
		set_page_address(2,3);
		send_data(vertLine);

        set_column_address(76,83);
		set_page_address(2,3);
		send_data(zero);

		set_column_address(85,92);
		set_page_address(2,3);
		send_data(x);
	}

	else
	{
		set_column_address(12,19);
		set_page_address(2,3);
		send_data(blank);

		set_column_address(21,28);
		set_page_address(2,3);
		send_data(blank);

        set_column_address(58,65);
		set_page_address(2,3);
		send_data(blank);

        set_column_address(76,83);
		set_page_address(2,3);
		send_data(blank);

		set_column_address(85,92);
		set_page_address(2,3);
		send_data(blank);
	}

    //Address
	set_column_address(30,37);
	set_page_address(2,3);
	send_data(code2[0]);

	set_column_address(39,46);
	set_page_address(2,3);
	send_data(code2[1]);

    //Data
	set_column_address(94,101);
	set_page_address(2,3);
	send_data(code2[2]);

	set_column_address(103,110);
	set_page_address(2,3);
	send_data(code2[3]);

	//page 4 & 5
	if(isBlank3() == false)
	{
		set_column_address(12,19);
		set_page_address(4,5);
		send_data(zero);

		set_column_address(21,28);
		set_page_address(4,5);
		send_data(x);

        set_column_address(58,65);
		set_page_address(4,5);
		send_data(vertLine);

        set_column_address(76,83);
		set_page_address(4,5);
		send_data(zero);

		set_column_address(85,92);
		set_page_address(4,5);
		send_data(x);

	}

	else
	{
		set_column_address(12,19);
		set_page_address(4,5);
		send_data(blank);

		set_column_address(21,28);
		set_page_address(4,5);
		send_data(blank);

        set_column_address(58,65);
		set_page_address(4,5);
		send_data(blank);

        set_column_address(76,83);
		set_page_address(4,5);
		send_data(blank);

		set_column_address(85,92);
		set_page_address(4,5);
		send_data(blank);
	}


    //Address
	set_column_address(30,37);
	set_page_address(4,5);
	send_data(code3[0]);

	set_column_address(39,46);
	set_page_address(4,5);
	send_data(code3[1]);

    //Data
	set_column_address(94,101);
	set_page_address(4,5);
	send_data(code3[2]);

	set_column_address(103,110);
	set_page_address(4,5);
	send_data(code3[3]);

	//page 6 & 7
	if(isBlank4() == false)
	{
		set_column_address(12,19);
		set_page_address(6,7);
		send_data(zero);

		set_column_address(21,28);
		set_page_address(6,7);
		send_data(x);

        set_column_address(58,65);
		set_page_address(6,7);
		send_data(vertLine);

        set_column_address(76,83);
		set_page_address(6,7);
		send_data(zero);

		set_column_address(85,92);
		set_page_address(6,7);
		send_data(x);
	}

	else
	{
		set_column_address(12,19);
		set_page_address(6,7);
		send_data(blank);

		set_column_address(21,28);
		set_page_address(6,7);
		send_data(blank);

        set_column_address(58,65);
		set_page_address(6,7);
		send_data(blank);

        set_column_address(76,83);
		set_page_address(6,7);
		send_data(blank);

		set_column_address(85,92);
		set_page_address(6,7);
		send_data(blank);
	}

    //Address
	set_column_address(30,37);
	set_page_address(6,7);
	send_data(code4[0]);

	set_column_address(39,46);
	set_page_address(6,7);
	send_data(code4[1]);

    //Data
	set_column_address(94,101);
	set_page_address(6,7);
	send_data(code4[2]);

	set_column_address(103,110);
	set_page_address(6,7);
	send_data(code4[3]);


}

void OLED::updateDisplay(Queue* values)
{
	int32_t displayValue;
	uint32_t upperAddress = 0;
	uint32_t lowerAddress = 0;
    uint32_t upperData = 0;
	uint32_t lowerData = 0;



	bool notEmpty = values->dequeue(&displayValue);

	if(notEmpty == false)
		return;

    upperAddress = ((((displayValue >> 8) & 0xFF) >> 4) & 0x0F);
    lowerAddress = (((displayValue >> 8) & 0xFF) & 0x0F);

	upperData = ((displayValue & 0xFF) >> 4) & 0x0F;
	lowerData = (displayValue & 0xFF) & 0x0F;



	set_code4(code3[0],code3[1],code3[2],code3[3]);
	set_code3(code2[0],code2[1],code2[2],code2[3]);
	set_code2(code1[0],code1[1],code1[2],code1[3]);

	switch(upperAddress)
	{
		case 0x00:
		{
			set_partial_code1(zero,0);
			break;
		}
		case 0x01:
		{
			set_partial_code1(one,0);
			break;
		}
		case 0x02:
		{
			set_partial_code1(two,0);
			break;
		}
		case 0x03:
		{
			set_partial_code1(three,0);
			break;
		}
		case 0x04:
		{
			set_partial_code1(four,0);
			break;
		}
		case 0x05:
		{
			set_partial_code1(five,0);
			break;
		}
		case 0x06:
		{
			set_partial_code1(six,0);
			break;
		}
		case 0x07:
		{
			set_partial_code1(seven,0);
			break;
		}
		case 0x08:
		{
			set_partial_code1(eight,0);
			break;
		}
		case 0x09:
		{
			set_partial_code1(nine,0);
			break;
		}
		case 0x0A:
		{
			set_partial_code1(A,0);
			break;
		}
		case 0x0B:
		{
			set_partial_code1(B,0);
			break;
		}
		case 0x0C:
		{
			set_partial_code1(C,0);
			break;
		}
		case 0x0D:
		{
			set_partial_code1(D,0);
			break;
		}
		case 0x0E:
		{
			set_partial_code1(E,0);
			break;
		}
		case 0x0F:
		{
			set_partial_code1(F,0);
			break;
		}
		default:
		{
			set_partial_code1(blank,0);
			break;
		}

	}


	switch(lowerAddress)
	{
		case 0x00:
		{
			set_partial_code1(zero,1);
			break;
		}
		case 0x01:
		{
			set_partial_code1(one,1);
			break;
		}
		case 0x02:
		{
			set_partial_code1(two,1);
			break;
		}
		case 0x03:
		{
			set_partial_code1(three,1);
			break;
		}
		case 0x04:
		{
			set_partial_code1(four,1);
			break;
		}
		case 0x05:
		{
			set_partial_code1(five,1);
			break;
		}
		case 0x06:
		{
			set_partial_code1(six,1);
			break;
		}
		case 0x07:
		{
			set_partial_code1(seven,1);
			break;
		}
		case 0x08:
		{
			set_partial_code1(eight,1);
			break;
		}
		case 0x09:
		{
			set_partial_code1(nine,1);
			break;
		}
		case 0x0A:
		{
			set_partial_code1(A,1);
			break;
		}
		case 0x0B:
		{
			set_partial_code1(B,1);
			break;
		}
		case 0x0C:
		{
			set_partial_code1(C,1);
			break;
		}
		case 0x0D:
		{
			set_partial_code1(D,1);
			break;
		}
		case 0x0E:
		{
			set_partial_code1(E,1);
			break;
		}
		case 0x0F:
		{
			set_partial_code1(F,1);
			break;
		}
		default:
		{
			set_partial_code1(blank,1);
			break;
		}

	}

	switch(upperData)
	{
		case 0x00:
		{
			set_partial_code1(zero,2);
			break;
		}
		case 0x01:
		{
			set_partial_code1(one,2);
			break;
		}
		case 0x02:
		{
			set_partial_code1(two,2);
			break;
		}
		case 0x03:
		{
			set_partial_code1(three,2);
			break;
		}
		case 0x04:
		{
			set_partial_code1(four,2);
			break;
		}
		case 0x05:
		{
			set_partial_code1(five,2);
			break;
		}
		case 0x06:
		{
			set_partial_code1(six,2);
			break;
		}
		case 0x07:
		{
			set_partial_code1(seven,2);
			break;
		}
		case 0x08:
		{
			set_partial_code1(eight,2);
			break;
		}
		case 0x09:
		{
			set_partial_code1(nine,2);
			break;
		}
		case 0x0A:
		{
			set_partial_code1(A,2);
			break;
		}
		case 0x0B:
		{
			set_partial_code1(B,2);
			break;
		}
		case 0x0C:
		{
			set_partial_code1(C,2);
			break;
		}
		case 0x0D:
		{
			set_partial_code1(D,2);
			break;
		}
		case 0x0E:
		{
			set_partial_code1(E,2);
			break;
		}
		case 0x0F:
		{
			set_partial_code1(F,2);
			break;
		}
		default:
		{
			set_partial_code1(blank,2);
			break;
		}

	}


	switch(lowerData)
	{
		case 0x00:
		{
			set_partial_code1(zero,3);
			break;
		}
		case 0x01:
		{
			set_partial_code1(one,3);
			break;
		}
		case 0x02:
		{
			set_partial_code1(two,3);
			break;
		}
		case 0x03:
		{
			set_partial_code1(three,3);
			break;
		}
		case 0x04:
		{
			set_partial_code1(four,3);
			break;
		}
		case 0x05:
		{
			set_partial_code1(five,3);
			break;
		}
		case 0x06:
		{
			set_partial_code1(six,3);
			break;
		}
		case 0x07:
		{
			set_partial_code1(seven,3);
			break;
		}
		case 0x08:
		{
			set_partial_code1(eight,3);
			break;
		}
		case 0x09:
		{
			set_partial_code1(nine,3);
			break;
		}
		case 0x0A:
		{
			set_partial_code1(A,3);
			break;
		}
		case 0x0B:
		{
			set_partial_code1(B,3);
			break;
		}
		case 0x0C:
		{
			set_partial_code1(C,3);
			break;
		}
		case 0x0D:
		{
			set_partial_code1(D,3);
			break;
		}
		case 0x0E:
		{
			set_partial_code1(E,3);
			break;
		}
		case 0x0F:
		{
			set_partial_code1(F,3);
			break;
		}
		default:
		{
			set_partial_code1(blank,3);
			break;
		}

	}
	set_OLED();
}

void OLED::send_command(uint8_t command)
{
    HAL_I2C_Mem_Write(&SSD1306_I2C_PORT,SSD1306_I2C_ADDR,0x00, 1, &command, 1, HAL_MAX_DELAY);
}

void OLED::send_data(uint8_t* data)
{
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1, data, CHARACTER_SIZE, HAL_MAX_DELAY);

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
}

void OLED::set_column_address(uint8_t begin, uint8_t end)
{
    //Horizontal addressing mode (ONE I'LL USE)
    send_command(SSD1306_SET_COLUMN_ADDR); //set Column address (make a function for this)
    send_command(begin); //column address/position start
    send_command(end); //column address/position end
}

void OLED::set_page_address(uint8_t begin, uint8_t end)
{
    //Horizontal addressing mode (ONE I'LL USE)
    send_command(SSD1306_SET_PAGE_ADDR); //set Column address (make a function for this)
    send_command(begin); //column address/position start
    send_command(end); //column address/position end
}

void OLED::fill_display()
{
	set_column_address(0,127);
		set_page_address(0,7);
		uint8_t fill[8][128] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

		for(int32_t i = 0; i < 8; i++)
		{

			send_data(fill[i]);

		}

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

}
