/*
 * logfile.c - Routines for logging data to MicroSD Card formatted
 * with a FAT32 filesystem.
 * 
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2023 Craig Peacock
 *
 * SPDX-License-Identifier: Apache-2.0
 */

struct logfile_t {
	struct k_work work;		/* Must be first parameter as we pass this to k_work_init() */
	struct fs_file_t file;
	struct k_timer timer;
};

void mount_disk(void);
void logfile_open(struct logfile_t *logfile, char *filename, k_work_handler_t work_log_handler, k_timeout_t period);
void logfile_write(struct logfile_t *logfile, char *buffer, size_t size);
void logfile_close(struct logfile_t *logfile);