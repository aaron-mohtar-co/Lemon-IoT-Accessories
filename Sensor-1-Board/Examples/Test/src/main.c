/*
 * Sensor 1 Example Source Code
 *  - Sensirion SHTCx Example
 *
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * SPDX-License-Identifier: Apache-2.0
 *
 * This example uses Zephyr Sensor Framework and DeviceTree overlays (at a 
 * project level) to obtain the temperature and humidity from a SHTC3 sensor.
 * 
 * API Reference:
 * https://docs.zephyrproject.org/latest/hardware/peripherals/sensor.html
 * https://docs.zephyrproject.org/3.0.0/reference/devicetree/bindings/sensor/sensirion%2Cshtcx.html
 * https://docs.zephyrproject.org/3.0.0/reference/devicetree/bindings/sensor/bosch%2Cbme680-i2c.html#dtbinding-bosch-bme680-i2c
 * 
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

void main(void)
{
	printk("Lemon IoT Sensor 1 running on %s\n", CONFIG_BOARD);

 	// Get a device structure from a devicetree node with compatible
 	// "sensirion,shtcx". 
	const struct device *dev_shtc = DEVICE_DT_GET_ANY(sensirion_shtcx);

	if (dev_shtc == NULL) {
		printk("\nError: No devicetree node found for Sensirion SHTCx.\n");
		return;
	}

	if (!device_is_ready(dev_shtc)) {
		printf("Device %s is not ready\n", dev_shtc->name);
		return;
	}

	printk("Found device %s. Reading sensor data\n", dev_shtc->name);

	// Get a device structure from a devicetree node with compatible
 	// "bosch,bme680". 
	const struct device *dev_bme = DEVICE_DT_GET_ANY(bosch_bme680);

	if (dev_bme == NULL) {
		printk("\nError: No devicetree node found for Boasch BME680.\n");
		return;
	}

	if (!device_is_ready(dev_bme)) {
		printf("Device %s is not ready\n", dev_bme->name);
		return;
	}

	printk("Found device %s. Reading sensor data\n", dev_bme->name);

	while (true) {
		struct sensor_value temp, hum, pres, gas;

		// Read Sensirion SHTC3
		sensor_sample_fetch(dev_shtc);
		sensor_channel_get(dev_shtc, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev_shtc, SENSOR_CHAN_HUMIDITY, &hum);
		printk("SHTC3:  %.2f degC, %0.2f%% RH\n", sensor_value_to_double(&temp), sensor_value_to_double(&hum));

		// Read Bosch BME680
		sensor_sample_fetch(dev_bme);
		sensor_channel_get(dev_bme, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev_bme, SENSOR_CHAN_HUMIDITY, &hum);
		sensor_channel_get(dev_bme, SENSOR_CHAN_PRESS, &pres);
		sensor_channel_get(dev_bme, SENSOR_CHAN_GAS_RES, &gas);
		printk("BME680: %.2f degC, %0.2f%% RH, %0.2f kPa, %0.0f ohms\n", 
			sensor_value_to_double(&temp), 
			sensor_value_to_double(&hum),
			sensor_value_to_double(&pres),
			sensor_value_to_double(&gas));

		k_sleep(K_MSEC(1000));
	}
}
