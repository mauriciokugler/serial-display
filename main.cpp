/*
Copyright (C) 2025 Mauricio Kugler
Embedded Systems & Instrumentation Department
École Supérieure d'Ingénieurs - ESIGELEC, France
This software is intended for research purposes only;
its redistribution is forbidden under any circumstances.
*/

#include "main.h"
#include "D7S4D.h"

//global variables
I2C_HandleTypeDef hi2c1;

int main(void)
{
	HAL_Init(); 			//reset peripherals, initializes flash interface and systick
	SystemClock_Config(); 	//system clock configuration

	//initialize peripherals
	MX_GPIO_Init();
	MX_I2C1_Init();

	D7S4D *display = new D7S4D(&hi2c1);

	while (true) {
		display->write(9999);
		HAL_Delay(500);

		display->write(-999);
		HAL_Delay(500);

		char txt[] = "0123";
		display->write(txt);
		HAL_Delay(500);

		for(unsigned int i=0;i<4;i++) {
			display->clear();
			display->digit(i,i+4);
			HAL_Delay(500);
		}

		display->hexa(0x89AB);
		HAL_Delay(500);

		for(unsigned int i=0;i<6;i++) {
			display->clear();
			display->decimal(0x01 << i);
			HAL_Delay(500);
		}

		int n[] = {0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0};
		int k[] = {1, 1, 1, 1, 2, 4, 8, 8, 8, 8, 16, 32};

		for(unsigned int i=0;i<12;i++) {
			display->clear();
			display->custom(n[i], k[i]);
			HAL_Delay(100);
		}

		display->hexa(0xCDEF);
		for(unsigned int i=0;i<100;i+=10) {
			display->brightness(i);
			HAL_Delay(250);
		}
	}
}

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
	HAL_IncTick();
}

#ifdef __cplusplus
}
#endif
