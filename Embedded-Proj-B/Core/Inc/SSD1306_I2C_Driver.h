/*
 * SSD1306_I2C_Driver.h
 *
 *  Created on: Sep 19, 2024
 *      Author: LogMa
 */
/*
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"
#include <cstdint>
#include <stdio.h>
#include "main.h"

#include "displayQueue.h"


#ifndef INC_SSD1306_I2C_DRIVER_H_
#define INC_SSD1306_I2C_DRIVER_H_

extern I2C_HandleTypeDef hi2c1;

#define SSD1306_I2C_PORT hi2c1

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#define SSD1306_BUFFER_SIZE SSD1306_WIDTH * SSD1306_HEIGHT / 8

//SAO = 0 then ADDR = 0x3C, SAO = 1 then ADDR = 0x3D
//I left shifted the ADDR by 1 because the list bit is the R/W# bit
#define SSD1306_I2C_ADDR 0x78


If D/C# pin is HIGH, D[7:0] is interpreted as display data written to Graphic Display Data RAM (GDDRAM).
If it is LOW, the input at D[7:0] is interpreted as a command.
Then data input will be decoded and written to the corresponding command register.
*/
/*
#define CHARACTER_SIZE 16
#define SSD1306_SET_COLUMN_ADDR 0x21
#define SSD1306_SET_PAGE_ADDR 0x22


class OLED{ // @suppress("Miss copy constructor or assignment operator")
private:
	//uint8_t character[16];
	displayQueue* queue;
	uint32_t waveFreq[4];

	//use these to compare the last struct to the new struct being dequeued
	displayValues storedValues;
	bool startUpF;
	bool startUpW;

	uint8_t channel;

	uint8_t code[6][16];


public:
	OLED(uint8_t,displayQueue*);

	//I2C commands to set the display up and set what it displays
	void send_command(uint8_t);
	void send_data(uint8_t*);

	//Background set up for the display to initialize and to be able to set positions on the display
	void set_OLED();
	void SSD1306_init();
	void set_column_address(uint8_t,uint8_t);
	void set_page_address(uint8_t,uint8_t);
	void clear_display();


	void set_partial_code(uint8_t*, uint8_t);

	void updateChannel_1();
	void updateChannel_2();


	void clearChannel_1();
	void clearChannel_2();

	void updateDisplay();

	void I2C_Initialize();

};

#endif  INC_SSD1306_I2C_DRIVER_H_ */
