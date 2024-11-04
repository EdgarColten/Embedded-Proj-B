/*
 * SSD1306_SPI_Driver.h
 *
 *  Created on: Oct 28, 2024
 *      Author: LogMa
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
	//uint8_t character[16];
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
	void send_command(uint8_t);
	void send_data(uint8_t*);

	//Background set up for the display to initialize and to be able to set positions on the display
	void set_OLED();
	void SSD1306_init();
	void set_column_address(uint8_t,uint8_t);
	void set_page_address(uint8_t,uint8_t);
	void clear_display();

	void set_partial_code(uint8_t*,uint8_t*);

	void updateChannel_1();
	void updateChannel_2();

	void clearChannel();

	void updateDisplay();

};


#endif /* INC_SSD1306_SPI_DRIVER_H_ */
