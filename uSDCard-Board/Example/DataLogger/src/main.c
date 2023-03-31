/*
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2023 Craig Peacock
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/fs/fs.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <zephyr/random/rand32.h>
#include "logfile.h"

void logfile_handler(struct k_work *item)
{
	struct logfile_t *logfile = (void *)item;
	char buffer[80];

	//
	// Add any variables and functions you wish to periodically log here
	//

	// Get local time
	struct tm tm;
	time_t now = time(NULL);
	localtime_r(&now, &tm);

	// Get param1, param2, param3
	uint32_t param1, param2, param3;
	param1 = sys_rand32_get();
	param2 = sys_rand32_get();
	param3 = sys_rand32_get();
	
	// Log to file
	sprintf(buffer, "%02d:%02d:%02d,%d,%d,%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, param1, param2, param3);
	logfile_write(logfile, buffer, strlen(buffer));
}

void main(void)
{
	struct logfile_t log;

	printk("MicroSD FAT32 Datalogger Example\nBoard: %s\n", CONFIG_BOARD);

	mount_disk();
	logfile_open(&log, "/SD:/data.log", logfile_handler, K_SECONDS(1));

	k_sleep(K_SECONDS(30));

	logfile_close(&log);
}