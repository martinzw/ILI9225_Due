# ILI9225_Due
Arduino Due library for interfacing with (write only) ILI9225-based TFTs

This library is intended to establish a fast connection to 2.0# ILI9225 based TFT displays for Arduino Due boards.

In comparison to existing libraries it uses Due's SPI DMA features to speed up the connection very much.

The library is based on other libraries, especially the ILI9341_Due library by Marek Buriak.
(https://github.com/marekburiak/ILI9341_Due),	Copyright (c) 2014  Marek Buriak
and
on ILI9225_t3.cpp by Bruce Tsao
(https://github.com/brucetsao/LIB_for_MCU/tree/master/Arduino_Lib/libraries/ILI9225_t3)

My work was to combine the fast DMA transaction features for Due by Mark Buriak
with the handling of ILI9225 used by Bruce Tsao and to get it working alltogether.

The Library is still "beta". Not everything has been tested.

But the benchmark and demo examples taken from Marek's Library have been tested to work.
