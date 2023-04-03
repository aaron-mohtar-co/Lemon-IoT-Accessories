# Battery Board

The Battery Board provides support for adding a Lithium battery to your Lemon IoT Processor Board. In addition, a PV solar panel can be added for longer outdoor deployments.

The board consists of:
* [TPS63031](https://www.ti.com/product/TPS63031) - High Efficiency Buck-Boost Converter to supply a constant 3.3V regardless of battery voltage.
* [BQ29702](https://www.ti.com/product/BQ2970) - Li-Ion/Li Polymer Advanced Single-Cell Battery Protector to disconnect the battery if the voltage falls below 2.80V or exceeds 4.35V.
* [BQ24210](https://www.ti.com/product/BQ24210) - 800mA Single-Cell Li-Ion Solar Battery Charger.

In addition to the above, version 1.1 provides support to measure the battery voltage and includes a power switch.

## Notes

* The BQ29702 Battery Protector is designed to disconnect the battery pack when the voltage falls below 2.80V and remain latched off until an external charger is applied. When an external battery is first attached, it will remain latched off until the solar panel is placed in the sun.

* On version 1.1, the switch disables the TPS63031 DC-DC Converter. However, due to the extremely low power consumption of many of the Lemon IoT processor boards, they can remain powered by high logic levels applied to GPIO pins. For example, if the board is still connected to the Development Board, a high logic level on the RXD pin can power the board via the ESD body protection diodes. In this configuration, the MCU may remain powered, even if the switch is off.

## Battery

* The battery can be any single-cell Lithium Ion or Lithium Polymer battery of suitable capacity.
* Battery connector is the common JST-PH (2mm pitch).
* If used, the BQ24210 Single-Cell Li-Ion Solar Battery Charger will charge the battery to 4.20V with a maximum current of 390mA.

## Solar Charger

* The solar charger can accept an input voltage up to 18V. 
* Maximum charging current is set at 390mA, but may be limited by your solar panel. 
* The charger has input voltage-based dynamic power management (DPM) that can throttle the current back as the voltage drops. This can be used to optimise PV solar power output by setting this close to the PV solar panel's maximum power point (MPP). Currently it is set to 6V to match the [90 x 60mm, 1 Watt solar panel (6V @ 166mA)](https://lemon-iot.com/index.php/product/lemon-iot-accessory-6v-solar-pv-panels/).   

## Compatibility

The Battery Board is compatible with the following processor boards:
* [Lemon-IoT-LTE-nRF9160](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nRF9160)
* [Lemon-IoT-BLE-nRF52840](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52840)
* [Lemon-IoT-BLE-nRF52832](https://github.com/aaron-mohtar-co/Lemon-IoT-BLE-nRF52832)
* [Lemon-IoT-LoRa-RAK3172](https://github.com/aaron-mohtar-co/Lemon-IoT-LoRa-RAK3172)
  
## Examples

The following examples are available:

* [ReadVoltage](https://github.com/aaron-mohtar-co/Lemon-IoT-Accessories/tree/main/Battery-Board/Examples/ReadVoltage) - Provides example and routines to measure battery voltage and processor VDD voltage.
