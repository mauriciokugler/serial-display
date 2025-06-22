/*
Copyright (C) 2024 Mauricio Kugler
Embedded Systems & Instrumentation Department
École Supérieure d'Ingénieurs - ESIGELEC, France
This software is intended for research purposes only;
its redistribution is forbidden under any circumstances.
*/

#ifndef D7S4DH
#define D7S4DH

//#include "stm32f0xx_hal.h"
#include "stm32f1xx_hal.h"		// must match target CPU!
//#include "stm32f4xx_hal.h"

class D7S4D
{
private:

	const uint8_t address = 0xE2;
	const unsigned int wait = 20;
	const unsigned int delay = 1;
	const uint8_t space = 0x20;
	const uint8_t minus = 0x2D;

	I2C_HandleTypeDef *hi2c;

	typedef enum {
		DIGIT_0	= (uint8_t)0x03,
		DIGIT_1	= (uint8_t)0x04,
		DIGIT_2	= (uint8_t)0x05,
		DIGIT_3	= (uint8_t)0x06
	} digits;

	void inline i2c_tx(uint8_t *data, uint16_t n) {
		HAL_I2C_Master_Transmit(hi2c, address, data, n, wait);
		HAL_Delay(delay);
	}

public:

	D7S4D(I2C_HandleTypeDef *di2c);

	typedef enum {
		//ADDRESS	= (uint8_t)0x80,
		//RESET		= (uint8_t)0x81,
		CLEAR	= (uint8_t)0x76,
		DECIMAL	= (uint8_t)0x77,
		CURSOR	= (uint8_t)0x79,
		BRIGHT	= (uint8_t)0x7A,
		CUSTOM	= (uint8_t)0x78
	} commands;

	typedef enum {
		APOSTROPHE	= 0x20,
		COLON		= 0x10,
		DECIMAL_3	= 0x08,
		DECIMAL_2	= 0x04,
		DECIMAL_1	= 0x02,
		DECIMAL_0	= 0x01
	} points;

	void write(int data);						// show integer value [-999 ... 9999]
	void write(char data[4]);					// show ASCII characters

	void hexa(int data);						// show hexadecimal value [0000 ... FFFF]

	void digit(uint8_t index, uint8_t data);	// write specific digit
	void decimal(int data);						// decimal point and apostrophe control

	void clear();								// clear display
	void cursor(uint8_t index);					// set cursor position [0, 1, 2, 3]
	void brightness(uint8_t data);				// brightness control [0 ... 100]
	void custom(uint8_t index, uint8_t data);	// show custom character

	void command(uint8_t data);					// execute custom command
};

#endif
