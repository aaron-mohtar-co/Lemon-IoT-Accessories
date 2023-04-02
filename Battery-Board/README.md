# Battery Board

The Battery Board provides support for adding a Lithium battery to your Lemon IoT Processor Board. In addition, a PV solar panel can be added for longer deployments.

The board consists of:
* [TPS63031](https://www.ti.com/product/TPS63031) - High Efficiency Buck-Boost Converter to supply a constant 3.3V regardless of battery voltage.
* [BQ29702](https://www.ti.com/product/BQ2970) - Li-Ion/Li Polymer Advanced Single-Cell Battery Protector
* [BQ24210](https://www.ti.com/product/BQ24210) - 800mA Single-Cell Li-Ion Solar Battery Charger

In addition to the above, version 1.1 provides support to measure the battery voltage.

## Notes

* The BQ29702 Battery Protector is designed to disconnect the battery pack when the voltage falls below 2.80V and remain latched off until an external charger is applied. When an external battery is first attached, it will remain latched off until the solar panel is placed in the sun.

* On version 1.1, the switch disables the TPS63031 DC-DC Converter. However, due to the extremely low power consumption of many of the Lemon IoT processor boards, they can remain powered by high logic levels applied to GPIO pins. For example, if the board is still connected to the Development Board, a high logic level on the RXD pin can power the board via the ESD body protection diodes. In this environment, the MCU may remain powered, even if the switch is off.

## Compatibility

The Battery Board is compatible with the following processor boards:
* [Lemon-IoT-LTE-nRF9160](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nRF9160)
* [Lemon-IoT-BLE-nRF52840](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52840)
* [Lemon-IoT-BLE-nRF52832](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52832)
* [Lemon-IoT-LoRa-RAK3172](https://github.com/aaron-mohtar-co/Lemon-IoT-LoRa-RAK3172)
  
## Examples

The following examples are available:

* [ReadVoltage](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/Battery-Board/Examples/ReadVoltage) - Provides example and routines to measure battery voltage and processor VDD voltage.
