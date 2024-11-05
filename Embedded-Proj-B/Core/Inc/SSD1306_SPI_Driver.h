/*
 * SSD1306_SPI_Driver.h
 *
 *  Created on: Oct 28, 2024
 *      Author: LogMa
 */

/**
 * @file "SSD1306_SPI_Driver.h"
 * @brief Display driver code
 */

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "stm32l4xx_it.h"
#include <cstdint>
#include <stdio.h>
#include "main.h"

#include "displayQueue.h"


#ifndef INC_SSD1306_SPI_DRIVER_H_
#define INC_SSD1306_SPI_DRIVER_H_

extern SPI_HandleTypeDef hspi1;


#define SSD1306_COMMAND_ENTIRE_DISPLAY_OFF 		0xA4
#define SSD1306_COMMAND_ENTIRE_DISPLAY_ON 		0xA5
#define SSD1306_COMMAND_SET_MUX 				0xA8
#define SSD1306_COMMAND_SET_OFFSET 				0xD3
#define SSD1306_COMMAND_START_LINE 				0x40
#define SSD1306_COMMAND_SEG_NORMAL 				0xA0
#define SSD1306_COMMAND_SEG_INVERSE 			0xA1
#define SSD1306_COMMAND_COM_NORMAL 				0xC0
#define SSD1306_COMMAND_COM_INVERSE 			0xC1
#define SSD1306_COMMAND_SET_COM_Hardware 		0xDA
#define SSD1306_COMMAND_CONTRAST_CONTROL 		0x81
#define SSD1306_COMMAND_DISPLAY_INVERSE_OFF 	0xA6
#define SSD1306_COMMAND_DISPLAY_INVERSE_ON 		0xA7
#define SSD1306_COMMAND_CLOCK_DIIVDER 			0xD5
#define SSD1306_COMMAND_DISPLAY_OFF 			0xAE
#define SSD1306_COMMAND_DISPLAY_ON 				0xAF
#define SSD1306_COMMAND_COM_SCAN_INVERSE 		0xC8
#define SSD1306_COMMAND_SET_LOWER_COLUMN 		0x00
#define SSD1306_COMMAND_SET_UPPER_COLUMN 		0x10
#define SSD1306_COMMAND_SET_PAGE 				0xB0
#define SSD1306_COMMAND_SET_CHARGE_PUMP		 	0xAD
#define SSD1306_COMMAND_SET_PRECHARGE_PERIOD	0xD9
#define SSD1306_COMMAND_SET_DISCHARGE 		 	0x22
#define SSD1306_COMMAND_VCOMH_DSEL_LEVEL 		0xDB
#define SSD1306_COMMAND_SET_DC_DC_ENABLE		0x8D
#define SSD1306_COMMAND_ADDRESSING_MODE			0x20



#define CHARACTER_SIZE 16
#define SSD1306_SET_COLUMN_ADDR 0x21
#define SSD1306_SET_PAGE_ADDR 0x22


class OLED{ // @suppress("Miss copy constructor or assignment operator")
private:
	displayQueue* queue;
	uint32_t waveFreq[4];
	uint32_t waveAmp[2];

	//use these to compare the last struct to the new struct being dequeued
	displayValues storedValues;


	uint8_t channel;

	uint8_t code[6][16];

	uint8_t frequency1[4][16];
	uint8_t amplitude1[3][16];
	uint8_t shape1[2][16];

	uint8_t frequency2[4][16];
	uint8_t amplitude2[3][16];
	uint8_t shape2[2][16];

	uint8_t SPI_RST_Count;
	uint8_t SPI_CS_count;

public:
	OLED(displayQueue*);

	//SPI commands to set the display up and set what it displays
	/**
	 * @brief Write a 8 bit command to change settings of the display.
	 * This function sets the D/C pin on the display low to let the display know that a "command" is being sent.
	 * This function then writes an 8 bit command to the display via SPI ustilzing the LL library.
	 * This function uses a while loop that lasts 2 us to check and verify that data has been transmitted and that the flag is not zero.
	 * 
	 * @param x command An unsigned integer used to send to the display. 
	 */
	void send_command(uint8_t);
	/**
	 * @brief Write an array that holds data to the display.
	 * This function sets the D/C pin on the display high to let the display know that "data" is being sent.
	 * This function itterates through a for loop that has a bond of #define CHARACTER_SIZE in this header file.
	 * This function sends 8-bits of data per iteration to the display via SPI ustilzing the LL library.
	 * This function uses a while loop that lasts 2 us to check and verify that data has been transmitted and that the flag is not zero.
	 * 
	 * @param x data An unsigned integer pointer of size #define CHARACTER_SIZE used to send data to the display. 
	 */
	void send_data(uint8_t*);
	/**
	 * @brief Sets the static letters to the display
	 * This function writes the static letters that will not be updated once the system is powered.
	 * This function only checks the value of the channel member variable in the OLED class and will display a 1 or 2 depending on its value.
	 */
	void set_OLED();
	/**
	 * @brief Sets initialization conditions to the display.
	 * This funstion sends commands to the display as defined in the SSD1306 datasheet to initialize the display.
	 */
	void SSD1306_init();
	/**
	 * @brief Sets the starting column address range that the display is permitted to write in.
	 * This function will take set the display to only write between the begining and end columns specified in the parameters.
	 * 
	 * @param x begin An unsigned integer used to tell the display the starting column to begin writing data to.
	 * @param x end An unsigned integer used to tell the display the ending column the display can write data to.
	 */
	void set_column_address(uint8_t,uint8_t);
	/**
	 * @brief Sets the starting page address range that the display is permitted to write in.
	 * This function will take set the display to only write between the begining and end pages specified in the parameters.
	 * 
	 * @param x begin An unsigned integer used to tell the display the starting page to begin writing data to.
	 * @param x end An unsigned integer used to tell the display the ending page the display can write data to.
	 */
	void set_page_address(uint8_t,uint8_t);
	/**
	 * @brief Clears the display
	 * This function sets every pixel in the display to 0.
	 */
	void clear_display();
	/**
	 * @brief used to set a specific index of an array to hold the value of a character that is defined in characters.h.
	 *  This function uses a for loop to iterate through each index of an array and match it to the corresponding index of the character array.
	 * @param x reading An unsigned integer array that is in charge of hold a character value of the same size and type.
	 * @param x value An unsigned integer array that defines the character whose data will be sent and shown on the display.
	 */
	void set_partial_code(uint8_t*,uint8_t*);

	/**
	 * @brief Updates the values displayed for each reading on the display for channel 1.
	 * This function sends data to the display to show the corresponding frequency value.
	 * This function sends data to the display to show the corresponding amplitude value.
	 * This function sends data to the display to show the corresponding shape.
	 */
	void updateChannel_1();
	/**
	 * @brief Updates the values displayed for each reading on the display for channel 2.
	 * This function sends data to the display to show the corresponding frequency value.
	 * This function sends data to the display to show the corresponding amplitude value.
	 * This function sends data to the display to show the corresponding shape.
	 * This function will also display what shift amount (in steps from 0 - 7) the shifted wave is in.
	 */
	void updateChannel_2();
	/**
	 * @brief This function determines what values should be sent to the display.
	 * This function takes the reading of the frequency for channel 1 and breaks the value down into separate variables.
	 * This function will take said variables and compare them to a certain number ranging between 0 and 9 and depending on the value set the character data.
	 * This function does the same process for amplitude, shape, and delay step.
	 */
	void updateDisplay();
};


#endif /* INC_SSD1306_SPI_DRIVER_H_ */
