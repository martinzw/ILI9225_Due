/*
graphicstestWithStats.ino - Test program for Arduino Due library for interfacing with (write only) ILI9225-based TFTs

Taken from Arduino Due library for interfacing with ILI9341-based TFTs
(https://github.com/marekburiak/ILI341_Due)
Copyright (c) 2014  Marek Buriak

	Library based on:
	ILI9341_due_.cpp - Arduino Due library for interfacing with ILI9341-based TFTs
	(https://github.com/marekburiak/ILI341_Due)
	Copyright (c) 2014  Marek Buriak

	This library is based on ILI9341_t3 library from Paul Stoffregen
	(https://github.com/PaulStoffregen/ILI9341_t3), Adafruit_ILI9341
	and Adafruit_GFX libraries from Limor Fried/Ladyada
	(https://github.com/adafruit/Adafruit_ILI9341).
	and on ILI9225_t3.cpp by Bruce Tsao
	(https://github.com/brucetsao/LIB_for_MCU/tree/master/Arduino_Lib/libraries/ILI9225_t3)

This file is part of the Arduino ILI9225_Due library.
Sources for this library can be found at https://github.com/martinzw/ILI9225_Due.

ILI9225_Due is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

ILI9225_Due is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with ILI9225_Due.  If not, see <http://www.gnu.org/licenses/>.
*/

	/***************************************************
	This is our GFX example for the Adafruit ILI9341 Breakout and Shield
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

//Path to SPI.h could be:
// "C:\Users\username\AppData\Local\arduino15\packages\arduino\hardware\sam\1.6.12\libraries\SPI\src\SPI.h"
#include <SPI.h>

#include <SystemFont5x7.h>
#include <ILI9225_due_config.h>
#include <ILI9225_due.h>

/*
 * Test_ILI9225_DMA.ino
 *
 * Created: 07.05.2019 17:57:01
 * Author: Martin Zwerschke
 */ 
 
#define TFT_RST 4
//DC is also called RS
#define TFT_DC 10    
//on Due only three Pins are possible for CS: 4, 10 or 52
#define TFT_CS 52

//Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//hardware SPI pins on Due are 110/SPI-Pin3 (SCK) , 108/SPI-Pin1 (MISO), 109/SPI-Pin4 (MOSI)            (SPI 6-pins near controller chip)
//Wire MISO to GND, because ILI9225 (at least on my board) can not be read and only one pin (SDI) is there. (SDA is missing.)
ILI9225_due tft = ILI9225_due(TFT_CS, TFT_DC, TFT_RST);

void setup() 
{
  Serial.begin(250000);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println(F("ILI9225 Test!")); 
 
  tft.begin();

//  // read diagnostics (optional but can help debug problems)
  //uint8_t x = tft.readcommand8(ILI9225_RDMODE);
  //Serial.print(F("Display Power Mode: 0x")); Serial.println(x, HEX);
  //x = tft.readcommand8(ILI9225_RDMADCTL);
  //Serial.print(F("MADCTL Mode: 0x")); Serial.println(x, HEX);
  //x = tft.readcommand8(ILI9225_RDPIXFMT);
  //Serial.print(F("Pixel Format: 0x")); Serial.println(x, HEX);
  //x = tft.readcommand8(ILI9225_RDIMGFMT);
  //Serial.print(F("Image Format: 0x")); Serial.println(x, HEX);
  //x = tft.readcommand8(ILI9225_RDSELFDIAG);
  //Serial.print(F("Self Diagnostic: 0x")); Serial.println(x, HEX); 
//  

  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.print(F("Screen fill              \t"));
  Serial.println(testFillScreen());
  delay(200);

  Serial.print(F("Text                     \t"));
  Serial.println(testText());
  delay(600);

  Serial.print(F("Lines                    \t"));
  Serial.println(testLines(ILI9225_CYAN));
  delay(200);

  Serial.print(F("Horiz/Vert Lines         \t"));
  Serial.println(testFastLines(ILI9225_RED, ILI9225_BLUE));
  delay(200);

  Serial.print(F("Rectangles (outline)     \t"));
  Serial.println(testRects(ILI9225_GREEN));
  delay(200);

  Serial.print(F("Rectangles (filled)      \t"));
  Serial.println(testFilledRects(ILI9225_YELLOW, ILI9225_MAGENTA));
  delay(200);

  Serial.print(F("Circles (filled)         \t"));
  Serial.println(testFilledCircles(10, ILI9225_MAGENTA));

  Serial.print(F("Circles (outline)        \t"));
  Serial.println(testCircles(10, ILI9225_WHITE));
  delay(200);

  Serial.print(F("Triangles (outline)      \t"));
  Serial.println(testTriangles());
  delay(200);
 
  Serial.print(F("Triangles (filled)       \t"));
  Serial.println(testFilledTriangles());
  delay(200);

  Serial.print(F("Rounded rects (outline)  \t"));
  Serial.println(testRoundRects());
  delay(200);

  Serial.print(F("Rounded rects (filled)   \t"));
  Serial.println(testFilledRoundRects());
  delay(200);

  Serial.println(F("Done!"));
  
}

void loop(void) 
{
  for(uint8_t rotation=0; rotation<4; rotation++) 
  {
    tft.setRotation((iliRotation)rotation,0);
    testText();
	delay(1000);
  } 

}

unsigned long testFillScreen() 
{
  unsigned long start = micros();
  tft.fillScreen(ILI9225_BLACK);
  tft.fillScreen(ILI9225_RED);
  tft.fillScreen(ILI9225_GREEN);
  tft.fillScreen(ILI9225_BLUE);
  tft.fillScreen(ILI9225_BLACK);
  return micros() - start;
}

unsigned long testText() 
{
  tft.fillScreen(ILI9225_BLACK);
  unsigned long start = micros();
  tft.cursorTo(0, 0);
  tft.setFont(SystemFont5x7);
  tft.setTextColor(ILI9225_WHITE);  tft.setTextScale(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9225_YELLOW); tft.setTextScale(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9225_RED);    tft.setTextScale(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9225_GREEN);
  tft.setTextScale(5);
  tft.println("Groop");
  tft.setTextScale(2);
  tft.println("I implore thee,");
  tft.setTextScale(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");

  return micros() - start;
}

unsigned long testLines(uint16_t color)
{
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9225_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(ILI9225_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9225_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9225_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) 
{
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9225_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color)
{
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9225_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) 
  {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) 
{
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9225_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) 
{
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9225_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) 
{
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() 
{
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9225_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() 
{
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9225_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() 
{
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9225_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects()
{
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9225_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}

