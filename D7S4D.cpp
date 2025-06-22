/*
Copyright (C) 2024 Mauricio Kugler
Embedded Systems & Instrumentation Department
École Supérieure d'Ingénieurs - ESIGELEC, France
This software is intended for research purposes only;
its redistribution is forbidden under any circumstances.
*/

#include "D7S4D.h"

//#define i2c_tx(data, n) { HAL_I2C_Master_Transmit(hi2c, address, data, n, wait); HAL_Delay(delay); }

D7S4D::D7S4D(I2C_HandleTypeDef *di2c)
{
	hi2c = di2c;
	clear();
}

void D7S4D::write(int data)
{
	uint8_t n[5];

	n[0] = CLEAR;

	if(data < 0) {
		data = -data;
		n[1] = (data<100) ? space : minus;
		n[2] = (data<100) ? ((data<10) ? space : minus) : (uint8_t)((data/100)%10);
		n[3] = (data<10) ? minus : (uint8_t)((data/10)%10);
		n[4] = (uint8_t)(data%10);
	}
	else {
		n[1] = (data<1000) ? space : (uint8_t)((data/1000)%10);
		n[2] = (data<100) ? space : (uint8_t)((data/100)%10);
		n[3] = (data<10) ? space : (uint8_t)((data/10)%10);
		n[4] = (uint8_t)(data%10);
	}

	i2c_tx(n,5);
}

void D7S4D::write(char data[4])
{
	clear();
	HAL_I2C_Master_Transmit(hi2c, address, (uint8_t*)data, 4, wait);
	i2c_tx((uint8_t*)data,4);
}

void D7S4D::hexa(int data)
{
	uint8_t n[5];

	n[0] = CLEAR;
	n[1] = (data<4096) ? space : (uint8_t)((data/4096)%16);
	n[2] = (data<256) ? space : (uint8_t)((data/256)%16);
	n[3] = (data<16) ? space : (uint8_t)((data/16)%16);
	n[4] = (uint8_t)(data%16);

	i2c_tx(n,5);
}

void D7S4D::digit(uint8_t index, uint8_t data)
{
	uint8_t n[3];

	n[0] = CURSOR;
	n[1] = (index < 3) ? index : 3;
	n[2] = data;

	i2c_tx(n,3);
}

void D7S4D::decimal(int data)
{
	uint8_t n[2];

	n[0] = DECIMAL;
	n[1] = (uint8_t)data;

	i2c_tx(n,2);
}

void D7S4D::clear()
{
	uint8_t n = CLEAR;
	i2c_tx(&n,1);
}

void D7S4D::cursor(uint8_t index)
{
	uint8_t n[2];

	n[0] = CURSOR;
	n[1] = (index < 4) ? index : 0;
	i2c_tx(n,2);
}

void D7S4D::brightness(uint8_t data)
{
	uint8_t n[2];

	n[0] = BRIGHT;
	n[1] = (data <= 100) ? data : 100;
	i2c_tx(n,2);
}

void D7S4D::custom(uint8_t index, uint8_t data)
{
	uint8_t n[2];

	n[0] = CUSTOM;
	n[1] = data;

	switch(index) {
		case 0: n[0] |= DIGIT_0; break;
		case 1: n[0] |= DIGIT_1; break;
		case 2: n[0] |= DIGIT_2; break;
		case 3: n[0] |= DIGIT_3; break;
	}

	i2c_tx(n,2);
}

void D7S4D::command(uint8_t data)
{
	i2c_tx(&data,1);
}
