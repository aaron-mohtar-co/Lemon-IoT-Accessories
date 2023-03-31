/*
 * logfile.c - Routines for logging data to MicroSD Card formatted
 * with a FAT32 filesystem.
 * 
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2023 Craig Peacock
 * Copyright (c) 2019 Tavish Naruka <tavishnaruka@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/storage/disk_access.h>
#include <zephyr/logging/log.h>
#include <zephyr/fs/fs.h>
#include <ff.h>
#include <stdio.h>
#include "logfile.h"

LOG_MODULE_REGISTER(SDCard);

void mount_disk(void)
{
	static const char *disk_pdrv = "SD";

	static FATFS fat_fs;

	static struct fs_mount_t mp = {
		.type = FS_FATFS,
		.mnt_point = "/SD:",
		.fs_data = &fat_fs,
	};

#ifdef PRINT_STATS
	uint64_t memory_size_mb;
	uint32_t block_count;
	uint32_t block_size;
#endif
	int ret;

	if (disk_access_init(disk_pdrv) != 0) {
		LOG_ERR("Error initialising disk.\n");
		return;
	}

#ifdef PRINT_STATS
	// The following calls are not mandatory. Used to display disk statistics.

	if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
		LOG_ERR("Unable to get sector count");
		return;
	}
	LOG_INF("Block count %u", block_count);

	if (disk_access_ioctl(disk_pdrv, DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
		LOG_ERR("Unable to get sector size");
		return;
	}

	memory_size_mb = (uint64_t)block_count * block_size;
	printk("Sector Size: %u bytes\n", block_size);
	printk("SD Card Size: %u megabytes\n", (uint32_t)(memory_size_mb >> 20));

#endif 

	ret = fs_mount(&mp);
	if (ret != FR_OK) {
		LOG_ERR("Error mounting disk.\n");
		return;
	}

	printk("Disk mounted.\n");
}

void logfile_timer_callback(struct k_timer *timer)
{
	struct k_work *work = timer->user_data;
	k_work_submit(work);
}

void logfile_open(struct logfile_t *logfile, char *filename, k_work_handler_t work_log_handler, k_timeout_t period)
{
	// Initialise file structure. Needs to be called before first use with fs_open().
	fs_file_t_init(&logfile->file);

	// Open file for appending. Create file if it doesn't exist.
	int ret = fs_open(&logfile->file, filename, FS_O_WRITE | FS_O_CREATE | FS_O_APPEND);
	if (ret != 0) {
		printk("fs_open() failed: ");
		switch (ret) {
			case -EINVAL:
				printk("invalid filename\n");
				break;
			case -ENOENT:
				printk("bad mount point\n");
				break;
			case -EROFS:
				printk("read-only\n");
				break;
			default:
				printk("(%d)", ret);
				break;
		}
	} else {

		// We pass our entire structure to k_work_init, so we can 
		// retrieve it in the handler. As such, the k_work structure
		// must be the first parameter in our structure:
		// https://github.com/zephyrproject-rtos/zephyr/issues/17410
		k_work_init((struct k_work *)logfile, work_log_handler);

		k_timer_init(&logfile->timer, logfile_timer_callback, NULL);
		logfile->timer.user_data = &logfile->work;
		k_timer_start(&logfile->timer, K_NO_WAIT, period);

		printk("Log file opened.\n");
	}
}

void logfile_write(struct logfile_t *logfile, char *buffer, size_t size)
{
	ssize_t bytes_written;

	bytes_written = fs_write(&logfile->file, buffer, size);
	if (bytes_written >= 0) {
		printk("Wrote %d bytes.\n", bytes_written);
	} else {
		LOG_ERR("fs_read failed (%d)\n",bytes_written);
	}
}

void logfile_close(struct logfile_t *logfile)
{
	k_timer_stop(&logfile->timer);

	int ret = fs_close(&logfile->file);
	if (ret != 0) {
		LOG_ERR("fs_close failed (%d)\n", ret);
		return;
	} else {
		printk("Log file closed.\n");
	}
}
