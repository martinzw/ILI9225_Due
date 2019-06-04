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

SPI-Clock divider and overclocking Arduino Due:

In "ILI9225_due_config.h" you can select the clock divider for SPI (#define ILI9225_SPI_CLKDIVIDER 2)
I wondered, why I could not succeed with divider = 1 here. The ILI simply did not work with this setting.
ILI9225 manual gave a hint: Minimal "Serial clock cycle time" is 20ns for writing (40ns for reading, which I do not use).
This gives us a maximum SPI-Clock of 50Mhz. So divider = 1 (resulting in 84MHz/2=42Mhz will work, but 84MHz/1= 84MHz surely will not, and in fact does not as stated above).
However, I read somewhere on the web that display controllers like the ILI9225 often allow to go beyond the specified maximum SPI-clock and wanted to check the limits.
But with Due-Clock of 84Mhz and divider 1 or 2 I could not do this.
So I looked for hints on overclocking Due and found it easy to realize (see demo program).
If you use 96MHz for Due's clock, the divider of 2 gives 48MHz SPI-Clock (inside ILI9225 specs).
Max overclocking for Due is 114MHz (using value 18UL instead of 15UL in overclocking code), giving us a SPI-Clock of 57MHz (outside ILI9225 specs). But even this setting works!
Can we even go higher? Yes we can, by using a different approach:
"underclock" Due to 60MHz (value 9UL in overclocking code), but change ILI9225_SPI_CLKDIVIDER to 1 in "ILI9225_due_config.h".
Of course the controller slows down (saving energy...) but SPI-transfers to ILI9225 work with 60MHz then.
Using 66MHz (value 10UL in overclocking code) reachs ILI9225's limit. Perhaps it works with short an twisted SPI-cables but you can no be sure.
With overclocked or underclocked Due you can not trust measured times, however. Because millis() and other things use F_CPU (wich still is 84MHz because it reads this constant from boards.txt in "Arduino15" folder) and some basic values are initialized before the overclocking is done, so changing boards.txt to different F_CPU alone will not be enough.
So if you want to benchmark, use a stop watch or simply trust your impression to proof the ILI9225's speed.


