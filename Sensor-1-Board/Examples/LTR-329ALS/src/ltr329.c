/* 
 * LTR-329ALS I2C Ambient Light Sensor
 * https://optoelectronics.liteon.com/en-global/led/index/Detail/926 
 *
 * Copyright 2023 Aaron Mothar & Co Pty Ltd
 * Copyright (c) Craig Peacock
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include "ltr329.h"

LOG_MODULE_REGISTER(ltr329, LOG_LEVEL_WRN);

uint8_t ltr329_init(const struct device *i2c_dev, struct ALS_t *light)
{
	uint8_t command[2];
	uint8_t data[2];

	// Reset Sensor
	command[0] = LTR329_ALS_CONTR;
	command[1] = 0x02;	// SW Reset
	i2c_write(i2c_dev, (uint8_t *)&command, 2, LTR329_I2C_ADDR);

	// Check Manufacturer ID
	command[0] = LTR329_MANUFAC_ID;
	i2c_write_read(i2c_dev, LTR329_I2C_ADDR, &command, 1, &data, 1);
	LOG_INF("Manufacturer ID = %02X\n", data[0]);

	// Check Part ID 
	command[0] = LTR329_PART_ID;
	i2c_write_read(i2c_dev, LTR329_I2C_ADDR, &command, 1, &data, 1);
	LOG_INF("Part Number ID = %02X, Revision = %02X\n", ((data[0] & 0xF0) >> 4), (data[0] & 0x0F));

	// Configure Sensor Measurement Rate & Integration Time 
	command[0] = LTR329_ALS_MEAS_RATE;
	command[1] = 0b00001101; // Measurement rate = 2s ; Integration time = 50ms 
	i2c_write(i2c_dev, (uint8_t *)&command, 2, LTR329_I2C_ADDR);

	light->integration_time = 0b001;
}

uint8_t ltr329_set(const struct device *i2c_dev, uint8_t mode, uint8_t gain)
{
	uint8_t command[2];

	// ALS Control
	command[0] = LTR329_ALS_CONTR;
	// Set Gain 
	command[1] = (gain && 0x7) << 2;

	if (mode == LTR329_MODE_ACTIVE) {
		command[1] = command[1] + 0b1;
	}
	if (mode == LTR329_MODE_STANDBY) {
		// no action (bit 0 already clear) 
	}
	if (mode == LTR329_MODE_SWRESET) {
		command[1] = command[1] + 0b10;
	}

	LOG_INF("Setting LTR329_ALS_CONTR to 0x%02X\n", command[1]);
	i2c_write(i2c_dev, (uint8_t *)&command, 2, LTR329_I2C_ADDR);
}

uint8_t ltr329_measure(const struct device *i2c_dev, struct ALS_t *light)
{
	uint8_t command[2];
	uint8_t data[4];

	// Read Status; Check ALS Data Status bit for New Data
	for (int i = 0; i <= 10; i++) {
		command[0] = LTR329_ALS_STATUS;
		i2c_write_read(i2c_dev, LTR329_I2C_ADDR, &command, 1, &data, 1);
		LOG_DBG("Status = %02X\n", data[0]);
		if (data[0] & 0x04) break;
		else k_sleep(K_MSEC(20));
	}

	if (!(data[0] & 0x80)) {
		// ALS Data is valid
		light->gain = (data[0] & 0x70) >> 4;

		// The ALS_DATA registers should be read as a group, with the lower address read back first
		command[0] = LTR329_ALS_DATA_CH1_0;
		i2c_write_read(i2c_dev, LTR329_I2C_ADDR, &command, 1, &data, 4);

		light->ch1 = (uint16_t)data[0] + (((uint16_t)data[1])<<8);
		light->ch0 = (uint16_t)data[2] + (((uint16_t)data[3])<<8);
	} else {
		// ALS Data is Invalid
		LOG_ERR("Data is Invalid");
	}
}

float ltr329_convertlux(struct ALS_t *light)
{
	float als_lux;
	float ratio;
	uint8_t als_gain = 0;
	float als_int = 0;

	switch (light->gain) {
		case LTR329_GAIN_1X:
			als_gain = 1;
			break;

		case LTR329_GAIN_2X:
			als_gain = 2;
			break;

		case LTR329_GAIN_4X:
			als_gain = 4;
			break;

		case LTR329_GAIN_8X:
			als_gain = 8;
			break;

		case LTR329_GAIN_48X:
			als_gain = 48;
			break;

		case LTR329_GAIN_96X:
			als_gain = 96;
			break;
	}

	switch (light->integration_time){
		case LTR329_INT_50mS:
			als_int = 0.5;
			break;

		case LTR329_INT_100mS:
			als_int = 1.0;
			break;

		case LTR329_INT_150mS:
			als_int = 1.5;
			break;

		case LTR329_INT_200mS:
			als_int = 2.0;
			break;

		case LTR329_INT_250mS:
			als_int = 2.5;
			break;

		case LTR329_INT_300mS:
			als_int = 3.0;
			break;

		case LTR329_INT_350mS:
			als_int = 3.5;
			break;

		case LTR329_INT_400mS:
			als_int = 4.0;
			break;
	}

	ratio = (float)light->ch1 / (light->ch0 + light->ch1);

	LOG_DBG("Channel 0 = %05d, Channel 1 = %05d\n", light->ch0, light->ch1);
	LOG_DBG("Gain = %d, Int Time = %.01f\n", als_gain, als_int);
	LOG_DBG("Ratio = %0.3f\n", ratio);

	if (ratio < 0.45) {
		LOG_DBG("ratio < 0.45\n");
		als_lux = (1.7732 * light->ch0 + 1.1059 * light->ch1) / als_gain / als_int;
	} else if (ratio < 0.64) {
		LOG_DBG("ratio < 0.64 && ratio >= 0.45\n");
		als_lux = (4.2785 * light->ch0 + 1.9548 * light->ch1) / als_gain / als_int;
	} else if (ratio < 0.85) {
		LOG_DBG("< 0.85 && ratio >= 0.64\n");
		als_lux = (0.5926 * light->ch0 + 0.1185 * light->ch1) / als_gain / als_int;
	} else {
		als_lux = 0;
	}

	return(als_lux);
}