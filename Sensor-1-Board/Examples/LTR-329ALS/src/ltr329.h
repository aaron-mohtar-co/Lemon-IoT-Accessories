/* 
 * LTR-329ALS I2C Ambient Light Sensor
 * https://optoelectronics.liteon.com/en-global/led/index/Detail/926 
 *
 * Copyright 2023 Aaron Mothar & Co Pty Ltd
 * SPDX-License-Identifier: Apache-2.0
 */

struct ALS_t {
	uint16_t ch0;
	uint16_t ch1;
	uint8_t gain;
	uint8_t integration_time;
};

uint8_t ltr329_init(const struct device *i2c_dev, struct ALS_t *light);
uint8_t ltr329_set(const struct device *i2c_dev, uint8_t mode, uint8_t gain);
uint8_t ltr329_measure(const struct device *i2c_dev, struct ALS_t *light);
float ltr329_convertlux(struct ALS_t *light);

#define LTR329_I2C_ADDR				0x29

#define LTR329_ALS_CONTR			0x80
#define LTR329_ALS_MEAS_RATE		0x85
#define LTR329_PART_ID				0x86
#define LTR329_MANUFAC_ID			0x87
#define LTR329_ALS_DATA_CH1_0		0x88
#define LTR329_ALS_DATA_CH1_1		0x89
#define LTR329_ALS_DATA_CH0_0		0x8A
#define LTR329_ALS_DATA_CH0_1		0x8B
#define LTR329_ALS_STATUS			0x8C

#define LTR329_MODE_STANDBY			0
#define LTR329_MODE_ACTIVE			1
#define LTR329_MODE_SWRESET			2

#define LTR329_GAIN_1X				0b000	/*!< Gain x1 -> range: 1 lux to 64k lux */
#define LTR329_GAIN_2X				0b001	/*!< Gain x2 -> range: 0.5 lux to 32k lux */
#define LTR329_GAIN_4X				0b010	/*!< Gain x4 -> range: 0.25 lux to 16k lux */
#define LTR329_GAIN_8X				0b011	/*!< Gain x8 -> range: 0.125 lux to 8k lux */
#define LTR329_GAIN_48X				0b110	/*!< Gain x48 -> range: 0.02 lux to 1.3k lux */
#define LTR329_GAIN_96X				0b111	/*!< Gain x96 -> range: 0.01 lux to 600 lux */

#define LTR329_INT_100mS			0b000
#define LTR329_INT_50mS 			0b001
#define LTR329_INT_200mS			0b010
#define LTR329_INT_400mS			0b011
#define LTR329_INT_150mS			0b100
#define LTR329_INT_250mS			0b101
#define LTR329_INT_300mS			0b110
#define LTR329_INT_350mS			0b111