# Micro SD Card Companion Board

The Micro SD Card Companion is ideal for data logging applications, allowing developers to store large amounts of data to removable non-volatile flash memory.

<P ALIGN="CENTER"><IMG SRC="https://lemon-iot.com/wp-content/uploads/2023/03/Lemon-IoT-uSD-diagram.jpeg" width=50% height=50%></P>

## Compatibility

The Micro SD Card Companion is compatible with the following boards:
* [Lemon-IoT-LTE-nRF9160](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nRF9160)
* [Lemon-IoT-BLE-nRF52840](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52840)

It is not compatible with the following boards:
  
* [Lemon-IoT-BLE-nRF52832](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52832) - The nRF52832 reset pin (P0.21) shares the same I/O line as MOSI. While the reset line can be reassigned, the hardware has a 0.1uF capacitor that effects signal integrity.
  
## Examples

The following examples are available:
* [uSDCard](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/uSDCard-Board/Examples/uSDCard) - Provides basic source-code for mounting a filesystem, writing and reading to a file. 
* [Datalogger](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/uSDCard-Board/Examples/DataLogger) - Provides a framework to periodically log data to MicroSD Card. Example file is comma-delimited, but can also be single line log messages.
