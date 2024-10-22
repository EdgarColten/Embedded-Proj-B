/*
 * characters.cpp
 *
 *  Created on: Sep 21, 2024
 *      Author: LogMa
 */
#include "characters.h"


//done
uint8_t x[16] = {
		0x00,	0x10,	0x20,	0x40,	0x80,	0x40,	0x20,	0x10,
		0x00,   0x08,   0x04,   0x02,   0X01,   0x02,   0x04,    0x08

};

uint8_t zero[16]= {

		0x00,	0XFC,	0X02,	0X02,	0X02,	0X02,	0XFC,	0x00,
		0x00,	0x3F,	0X40,	0X40,	0X40,	0X40,	0x3F,	0x00,

};

uint8_t one[16]= {

		0x00,	0x08,	0X04,	0X02,	0XFF,	0x00,	0x00,	0x00,
		0x00,	0x40,	0x40,	0x40,	0X7F,	0x40,	0x40,	0x00

};

uint8_t two[16]= {

		0x00,	0x0C,	0x06,	0x02,	0x02,	0x84,	0x78,	0x00,
		0x00,	0x7C,	0X42,	0X41,	0X41,	0X40,	0X40,	0x00

	//0X7C, 0X42, 0X42, 0X41, 0x41, 0x40, 0x40, 0x00

};

uint8_t three[16]= {

		0x00,	0x06,	0x82,	0x82,	0x82,	0x86,	0x7C,	0x00,
		0x00,	0X60,	0X40,	0X40,	0X40,	0x61,	0x3E,	0x00

};

uint8_t four[16]= {

		0x00,	0xE0,	0x10,	0x08,	0x04,	0xFE,	0x00,	0x00,
		0x00,	0x01,	0x01,	0x01,	0x01,	0xFF,	0x01,	0x00

};

uint8_t five[16]= {

		0x00,	0x7E,	0x42,	0x42,	0x42,	0x82,	0x02,	0x00,
		0x00,	0x60,	0x40,	0x40,	0x40,	0x60,	0x3F,	0x00

};

uint8_t six[16]= {

		0x00,	0xFC,	0X82,	0X82,	0X82,	0X82,	0x0E,	0x00,
		0x00,	0X3F,	0X40,	0X40,	0X40,	0X40,	0X3F,	0x00

};

uint8_t seven[16]= {

		0X00,	0X0E,	0X82,	0X82,	0xE2,	0x92,	0x8E,	0x00,
		0X00,	0X00,	0X00,	0X00,	0X7F,	0X00,	0X00,	0X00

};

uint8_t eight[16]= {

		0x00,	0XFC,	0X82,	0X82,	0X82,	0X82,	0XFC,	0x00,
		0x00,	0x3F,	0X40,	0X40,	0X40,	0X40,	0x3F,	0x00
/*
 * 0x38, 0X44, 0X82, 0X82, 0x82, 0x82, 0x44, 0x38,
	0X1C, 0X22, 0X41, 0X41, 0X41, 0X41, 0X22, 0x1C
 */
};

uint8_t nine[16]= {

		0x00,	0X7C,	0X82,	0X82,	0X82,	0X82,	0xFC,	0x00,
		0x00,	0x00,	0x40,	0x40,	0x40,	0x40,	0x3F,	0x00

};
/////////////////////////

//Not done
uint8_t A[16]= {
		0x00,	0xF8,	0x04,	0x02,	0x02,	0x04,	0xF8,	0x00,
		0x00,	0x7F,	0x01,	0x01,	0x01,	0x01,	0x7F,	0x00

};

uint8_t B[16]= {

		0x00,	0xFE,	0x82,	0x82,	0x7C,	0x00,	0x00,	0x00,
		0x00,	0x7F,	0x41,	0x41,	0x41,	0x3E,	0x00,	0x00

};

uint8_t C[16]= {

		0x00,	0xFC,	0x02,	0x02,	0x02,	0x0C,	0x00,	0x00,
		0x00,	0x3F,	0x40,	0x40,	0x40,	0x30,	0x00,	0x00
};


uint8_t D[16]= {

		0x00,	0xFE,	0x02,	0x02,	0x02,	0xFC,	0x00,	0x00,
		0x00,	0x7F,	0x40,	0x40,	0x40,	0x3F,	0x00,	0x00

};


uint8_t E[16]= {
		0x00,	0xFE,	0x82,	0x82,	0x82,	0x82,	0x00,	0x00,
		0x00,	0x7F,	0x40,	0x40,	0x40,	0x40,	0x00,	0x00

};

uint8_t F[16]= {
		0x00,	0xFE,	0x82,	0x82,	0x82,	0x82,	0x00,	0x00,
		0x00,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00

};

uint8_t R[16] = {
		0x00,	0XFE,	0X82,	0X82,	0X82,	0X82,	0X7C,	0x00,
		0x00,	0x7F,	0x00,	0x00,	0x00,	0x7F,	0x00,	0x00

};

uint8_t Q[16] = {
		0x00,	0XFC,	0X02,	0X02,	0X02,	0X02,	0XFC,	0x00,
		0x00,	0x1F,	0X20,	0X20,	0X38,	0X30,	0x7F,	0x40

};

uint8_t H[16] = {
		0x00,	0xFE,	0x80,	0x80,	0x80,	0x80,	0xFE,	0x00,
		0x00,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x7F,	0x00

};

uint8_t SQUARE[16] = {
		0x00,	0x00,	0xFE,	0x02,	0x02,	0xFE,	0x00,	0x00,
		0x40,	0x40,	0x7F,	0x00,	0x00,	0x7F,	0x40,	0x40
};

uint8_t SINE1[16] = {
		0x00,	0x00,	0xC0,	0x70,	0x08,	0x08,	0x08,	0x70,
		0x1C,	0x07,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,

};

uint8_t SINE2[16] = {
		0xC0,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
		0x01,	0x0E,	0x38,	0x40,	0x40,	0x40,	0x38,	0x07

};

uint8_t PULSE[16] = {
		0x00,	0x00,	0x00,	0x00,	0xFE,	0x02,	0xFE,	0x00,
		0x40,	0x40,	0x40,	0x40,	0x7F,	0x00,	0x7F,	0x40

};

uint8_t DELAY[16] = {

};




uint8_t blank[16]= {

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

uint8_t equal[16] = {
		0x00,	0x40,	0x40,	0x40,	0x40,	0x40,	0x40,	0x00,
		0x00,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x00
};

uint8_t b[16] = {
		0x00,	0xFE,	0x40,	0x40,	0xC0,	0x00,	0x00,	0x00,
		0x00,	0x3F,	0x40,	0x40,	0x7F,	0x00,	0x00,	0x00

};

uint8_t t[16] = {
		0X00,	0X00,	0X80,	0X80,	0xFE,	0X80,	0X80,	0x00,
		0X00,	0X00,	0X00,	0X00,	0X7F,	0X00,	0X00,	0X00

};

uint8_t n[16] = {
		0x00,	0XC0,	0X80,	0X80,	0X80,	0X80,	0X00,	0x00,
		0x00,	0x7F,	0x00,	0x00,	0x00,	0x00,	0x7F,	0x00

};

uint8_t power[16]= {

	0x00, 0XE0, 0x00, 0XF8, 0XF8, 0x00, 0XE0, 0x00,
	0x00, 0x3F, 0X40, 0X40, 0X40, 0X40, 0x3F, 0x00

};

uint8_t vertLine[16]= {

	0x00, 0x00, 0x00, 0XFF, 0XFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0XFF, 0XFF, 0x00, 0x00, 0x00

};
