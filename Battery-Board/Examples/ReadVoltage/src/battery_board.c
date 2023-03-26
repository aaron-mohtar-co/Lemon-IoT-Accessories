/*
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
	#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

// Data of ADC io-channels specified in DeviceTree.
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
				DT_SPEC_AND_COMMA)
};

static const struct gpio_dt_spec gpio_vbat_mon_en = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), vbat_mon_en_gpios);
static const struct gpio_dt_spec gpio_charging = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), charging_gpios);

int batt_brd_init(void)
{
	int err;

	// Configure VBAT_MON_EN output GPIO Pin
	if (device_is_ready(gpio_vbat_mon_en.port)) {
		err = gpio_pin_configure_dt(&gpio_vbat_mon_en, GPIO_OUTPUT_INACTIVE);
		if (err < 0) {
			// Handle error
			return;
		}
	} else {
		return -1;
	}

	// Configure CHARGING input GPIO pin
	if (device_is_ready(gpio_charging.port)) {
		err = gpio_pin_configure_dt(&gpio_charging, GPIO_INPUT);
		if (err < 0) {
			// Handle error
			return;
		}
	} else {
		return -1;
	}

	// Configure ADC channels individually prior to sampling
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		// Print out configuration (for validating DeviceTree)

		//printk("Channel %d:\n", adc_channels[i].channel_id);
		//printk(" Resolution %d bits\n", adc_channels[i].resolution);
		//printk(" Oversampling %d times\n", adc_channels[i].oversampling);
		//printk(" Reference %dmV\n", adc_channels[i].vref_mv);
		//printk(" Gain %d\n", adc_channels[i].channel_cfg.gain);

		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device not ready\n");
			return;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return;
		}
	}
}

int32_t batt_brd_read_batt_volt(void)
{
	int16_t buf;
	int err;

	struct adc_sequence sequence = {
		.buffer = &buf,
		.buffer_size = sizeof(buf), // buffer size in bytes, not number of samples
		//channels, resolution, oversampling populated by adc_sequence_init_dt() from DeviceTree
	};

	// Populate channel, resolution and oversampling from DeviceTree
	(void)adc_sequence_init_dt(&adc_channels[0], &sequence);

	gpio_pin_set_dt(&gpio_vbat_mon_en, 1);
	k_sleep(K_MSEC(30));

	// Request a conversion
	err = adc_read(adc_channels[0].dev, &sequence);
	if (err < 0) {
		printk("Could not read (%d)\n", err);
		return -1;
	}

	//printk("Raw: %d, ", buf);
	gpio_pin_set_dt(&gpio_vbat_mon_en, 0);

	// Convert to scaled voltage (mV)
	int32_t val_mv = buf;
	err = adc_raw_to_millivolts_dt(&adc_channels[0], &val_mv);
	if (err < 0) {
		printk("Scaled value not avaliable\n");
		return -1;
	}

	return (val_mv * 2);
}

int32_t batt_brd_read_vdd_volt(void)
{
	int16_t buf;
	int err;

	struct adc_sequence sequence = {
		.buffer = &buf,
		.buffer_size = sizeof(buf), // buffer size in bytes, not number of samples
		//channels, resolution, oversampling populated by adc_sequence_init_dt() from DeviceTree
	};

	// Populate channel, resolution and oversampling from DeviceTree
	(void)adc_sequence_init_dt(&adc_channels[1], &sequence);

	// Request a conversion
	err = adc_read(adc_channels[1].dev, &sequence);
	if (err < 0) {
		printk("Could not read (%d)\n", err);
		return -1;
	}

	// Convert to scaled voltage (mV)
	int32_t val_mv = buf;
	err = adc_raw_to_millivolts_dt(&adc_channels[1], &val_mv);
	if (err < 0) {
		printk("Scaled value not avaliable\n");
		return -1;
	}

	return (val_mv);
}

bool batt_brd_is_charging(void)
{
	return (gpio_pin_get_dt(&gpio_charging));
}