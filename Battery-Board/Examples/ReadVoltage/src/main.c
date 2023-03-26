/*
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include "battery_board.h"

void main(void)
{
	printk("Lemon IoT Battery Board Example\nBoard: %s\n", CONFIG_BOARD);

	batt_brd_init();
	
	while (1) {
		printk("Batt = %dmV, VDD = %dmV, Charging = %d\n", batt_brd_read_batt_volt(), batt_brd_read_vdd_volt(), batt_brd_is_charging());
		k_sleep(K_MSEC(1000));
	}
}
