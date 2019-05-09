/*
v0.1
ILI9225_Due_config.h - Arduino Due library for interfacing with (write only) ILI9225-based TFTs

Copyright (c) 2019 by Martin Zwerschke	

	based on the Library ILI9341_Due
	v1.01.008
	ILI9341_Due - Arduino Due library for interfacing with ILI9341-based TFTs

	Code: https://github.com/marekburiak/ILI9341_due
	Documentation: http://marekburiak.github.io/ILI9341_due/

	Copyright (c) 2015  Marek Buriak

	2.4 TFT Pin-out
	T_IRQ T_DO T_DIN T_CS T_CLK MISO LED CLK MOSI DC RESET CS GND VCC

	This library is based on ILI9225_t3 library from Paul Stoffregen
	(https://github.com/PaulStoffregen/ILI9225_t3), Adafruit_ILI9225
	and Adafruit_GFX libraries from Limor Fried/Ladyada
	(https://github.com/adafruit/Adafruit_ILI9225).
	and on ILI9225_t3.cpp by Bruce Tsao
	(https://github.com/brucetsao/LIB_for_MCU/tree/master/Arduino_Lib/libraries/ILI9225_t3)

This file is part of the Arduino ILI9225_due library.
Sources for this library can be found at 
https://github.com/martinzw/ILI9225_Due.

ILI9225_due is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

ILI9225_due is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with ILI9225_due.  If not, see <http://www.gnu.org/licenses/>.
*/

	/***************************************************
	This is our library for the Adafruit ILI9225 Breakout and Shield
	----> http://www.adafruit.com/products/1651

	Check out the links above for our tutorials and wiring diagrams
	These displays use SPI to communicate, 4 or 5 pins are required to
	interface (RST is optional)
	Adafruit invests time and resources providing this open source code,
	please support Adafruit and open-source hardware by purchasing
	products from Adafruit!

	Written by Limor Fried/Ladyada for Adafruit Industries.
	MIT license, all text above must be included in any redistribution
	****************************************************/

*/

#ifndef _ILI9225_due_configH_
#define _ILI9225_due_configH_

// comment out the SPI mode you want to use (does not matter for AVR)
//#define ILI9225_SPI_MODE_NORMAL	// uses SPI library
//#define ILI9225_SPI_MODE_EXTENDED	// uses Extended SPI in Due, make sure you use pin 4, 10 or 52 for CS
#define ILI9225_SPI_MODE_DMA		// uses DMA in Due

// set the clock divider
#if defined ARDUINO_SAM_DUE
#define ILI9225_SPI_CLKDIVIDER 2	// for Due
#elif defined ARDUINO_ARCH_AVR
#define ILI9225_SPI_CLKDIVIDER SPI_CLOCK_DIV2	// for Uno, Mega,...
#endif

// uncomment if you want to use SPI transactions. Uncomment it if the library does not work when used with other libraries.
//#define ILI_USE_SPI_TRANSACTION

// comment out if you do need to use scaled text. The text will draw then faster.
#define TEXT_SCALING_ENABLED

// default letter spacing
#define DEFAULT_LETTER_SPACING 2

// default line spacing
#define DEFAULT_LINE_SPACING 0

// sets the space between lines as part of the text
//#define LINE_SPACING_AS_PART_OF_LETTERS

// number representing the maximum angle (e.g. if 100, then if you pass in start=0 and end=50, you get a half circle)
// this can be changed with setArcParams function at runtime
#define DEFAULT_ARC_ANGLE_MAX 360		

// rotational offset in degrees defining position of value 0 (-90 will put it at the top of circle)
// this can be changed with setAngleOffset function at runtime
#define DEFAULT_ANGLE_OFFSET -90	




#endif
