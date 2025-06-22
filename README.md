# Serial 7-Segment Display STM32 HAL Driver

Yet another C++ driver for the [Sparkfun SparkFun 7-Segment Serial Display](https://www.sparkfun.com/sparkfun-7-segment-serial-display-red.html). This class provides simple methods for displying data in ASCII and hexadcecimal formats, decimal points, custom characters and brightness control.

This driver was developed for my own convenience, and it is by no means the best implementation approach. Use it at your own risk.

More detailed information about the hardware and firmware interfaces can be found in the [original respository](https://github.com/sparkfun/Serial7SegmentDisplay/wiki).

## Setup

The [D7S4D.h](https://github.com/mauriciokugler/serial-display/blob/main/D7S4D.h) header file should include the HAL header for STM32 family corresponding to the the target CPU. The code has benn tested with STM32F0, STM32F1 and STM32F4 families.

```C++
//#include "stm32f0xx_hal.h"
#include "stm32f1xx_hal.h"		// must match target CPU!
//#include "stm32f4xx_hal.h"
```

## Usage

The class constructor receives the pointer to the I<sup>2</sup>C object corresponding to the 7-segment display. The device should already been initialized using the HAL driver functions.

```C++
D7S4D *display = new D7S4D(&hi2c1);
```

Integers between -999 to 9999 can be displayed as follows, and the negative sign is displayed automatically in the first digit:

```C++
display->write(-123);
```

ASCII characters are displayed as follows, although [not all characters can be displayed](https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Basic-Usage#which-bytes-are-displayable).

```C++
char txt[] = "0123";
display->write(txt);
```

The brightness can be set to any integer values between 0 and 100:

```C++
display->brightness(75);
```

## Example

The `main.cpp` file contains a simple example of most available functions. Note that this example is just a simplified summary and __will not compile on its own__. For instance, all initialization functions have been omited for simplicity. In order to have a fully functional example, create a project using [STM32CubeIDE](https://wiki.st.com/stm32mpu/wiki/How_to_get_started_with_STM32CubeIDE_from_scratch) or any other compatible toolchain.

```C++
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
```
## Citing

```TeX
@MISC{Kugler2025,
  author = "Mauricio Kugler",
  title = "Serial 7-Segment Display STM32 HAL Driver",
  year = "2025",
  url = "https://github.com/mauriciokugler/serial-display",
  note = "Version 1.0.0"
}
```

## License

This project is licensed under the [MIT License](LICENSE).