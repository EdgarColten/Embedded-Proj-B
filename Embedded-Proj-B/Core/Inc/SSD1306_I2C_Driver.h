/*
 * SSD1306_I2C_Driver.h
 *
 *  Created on: Sep 19, 2024
 *      Author: LogMa
 */

#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"
#include <cstdint>
#include <stdio.h>
#include "main.h"

#include "Queue.h"


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

/*
If D/C# pin is HIGH, D[7:0] is interpreted as display data written to Graphic Display Data RAM (GDDRAM).
If it is LOW, the input at D[7:0] is interpreted as a command.
Then data input will be decoded and written to the corresponding command register.
*/
#define CHARACTER_SIZE 16
#define SSD1306_SET_COLUMN_ADDR 0x21
#define SSD1306_SET_PAGE_ADDR 0x22


class OLED{
private:
	//uint8_t character[16];
	uint8_t code1[4][16];
	uint8_t code2[4][16];
	uint8_t code3[4][16];
	uint8_t code4[4][16];

public:
	OLED();
	void send_command(uint8_t);
	void send_data(uint8_t*);
	void set_OLED();
	void SSD1306_init();
	void set_column_address(uint8_t,uint8_t);
	void set_page_address(uint8_t,uint8_t);
	void fill_display();
	void clear_display();
	bool isBlank1();
	bool isBlank2();
	bool isBlank3();
	bool isBlank4();
	void set_partial_code1(uint8_t*, uint8_t);
    void set_code1(uint8_t*,uint8_t*,uint8_t*, uint8_t*);
	void set_code2(uint8_t*,uint8_t*,uint8_t*, uint8_t*);
	void set_code3(uint8_t*,uint8_t*,uint8_t*, uint8_t*);
	void set_code4(uint8_t*,uint8_t*,uint8_t*, uint8_t*);
	void updateDisplay(Queue*);

};

#endif /* INC_SSD1306_I2C_DRIVER_H_ */
