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
See this short video:

https://www.youtube.com/embed/-lvQcEdbCPM

SPI Transactions:
If the controller has to communicate with more than one SPI device at a time, transfer settings can be different for the different devices. The Arduino libraries take care of that in newer library versions by holding a set of settings for each SPI device.
Starting a transaction for a device resumes the correct settings for this device and blocks other SPI interrupts until the transaction is finished with the endTransision command.
If you only use the ILI9225 Display as the single device on the SPI Bus, you do not need transactions.
look at: https://www.arduino.cc/en/Tutorial/SPITransaction
