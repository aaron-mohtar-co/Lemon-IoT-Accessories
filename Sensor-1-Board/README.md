# Environmental Sensor Companion Board

Add an affordable environment sensor to your Lemon IoT based project. This board measures ambient temperature, relative humidity and ambient light.

The board contains the following sensors:

* [Bosch BME680 Gas Sensor](https://www.bosch-sensortec.com/products/environmental-sensors/gas-sensors/bme680/) - Relative humidity, barometric pressure, ambient temperature and gas (VOC) sensor.
* [Sensirion SHTC3](https://sensirion.com/products/catalog/SHTC3/) - Relative humidity and ambient temperature sensor.
* [Lite-ON LTR-329ALS](https://optoelectronics.liteon.com/en-global/led/index/Detail/926) - Ambient light sensor. 

## Compatibility

The Micro SD Card Companion is compatible with the following boards:
* [Lemon-IoT-LTE-nRF9160](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nRF9160) - *Using P0.00/P0.01 (R5 and R7 fitted - default)*
* [Lemon-IoT-BLE-nRF52840](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52840) - *Using P0.27/P0.26 (R6 and R8 fitted)*
* [Lemon-IoT-BLE-nRF52832](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52832) - *Using P0.27/P0.26 (R6 and R8 fitted)*
  
## Examples

The following examples are available:

* [Test](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/Sensor-1-Board/Examples/Test) - Example showing the use of the Zephyr Sensor Subsystem to retrieve measurements from the Sensirion SHTC3 and Bosch BME680 Environmental Sensors.
* [LTR-329ALS](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/Sensor-1-Board/Examples/LTR-329ALS) - Example showing interrogating the LTR-329 Ambient light sensor using Zephyr I2C routines.
