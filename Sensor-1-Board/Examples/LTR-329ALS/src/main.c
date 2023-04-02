/*
 * LTR-329ALS Ambient Light Sensor Example
 *
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>
#include <stdio.h>
#include "ltr329.h"

void main(void)
{
	const struct device *dev_i2c;
	struct ALS_t light;

	printk("Lemon IoT LTR-329ALS Ambient Light Sensor\nBoard: %s\n", CONFIG_BOARD);

	dev_i2c = DEVICE_DT_GET(DT_ALIAS(ltr329bus));
	if (dev_i2c == 0) {
		printk("I2C: Device driver not found.\n");
		return;
	}
	
	printk("Found LTR329 I2C Bus\n");
	printk("Initialising Device\n");
	i2c_configure(dev_i2c, I2C_SPEED_SET(I2C_SPEED_STANDARD));
	ltr329_init(dev_i2c, &light);
	
	while(1) {
		// Switch to active mode
		ltr329_set(dev_i2c, LTR329_MODE_ACTIVE, LTR329_GAIN_1X);
		k_sleep(K_MSEC(50));
		// Retreive measurement
		ltr329_measure(dev_i2c, &light);
		// Switch back to low power mode
		ltr329_set(dev_i2c, LTR329_MODE_STANDBY, LTR329_GAIN_1X);	
		// Convert to Lux
		printk("Lux = %0.1f\n", ltr329_convertlux(&light));
		k_sleep(K_MSEC(1000));
	}
}
