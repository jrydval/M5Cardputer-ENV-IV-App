Project: ENV.IV Sensor App
=============================

Description:
------------
This embedded application for M5Cardputer reads and displays temperature, pressure, and humidity data from an ENV.IV environmental sensor connected via I2C.
The sensor contains BMP280 and SHT40 chips. It also sends the data over serial port in a simple "|" delimited format.

The firmware is developed using PlatformIO in Visual Studio Code and is intended for M5Cardputer.

Features:
---------
- Reads temperature, humidity, and barometric pressure.
- Communicates via I2C interface.
- Outputs sensor values to the display and serial port.

Hardware Requirements:
----------------------
- M5Cardputer
- ENV.IV sensor (connected via I2C)

Project Structure:
------------------
- src/             → Main source files
- platformio.ini   → Project and build configuration

License:
--------
MIT

Author:
-------
jrydval