/*
 * Copyright (c) 2023 Tai Jie Denny Yun <denny61302@gmail.com>
 * Copyright (c) 2023 Aaron Mohtar & Co Pty Ltd
 * Copyright (c) 2023 Craig Peacock
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>

#include "buttons.h"
#include "ui.h"

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

static lv_group_t *input_group;
static lv_indev_drv_t enc_drv;
static lv_indev_t *enc_indev;

static buttonId_t last_pressed;

static const int pwm_fequency = 500; // in Hz
static float input_period = (float)(1.0 / pwm_fequency) * 1000000000.0;
static int pwm_duty_cycle = 50; // in percentage

static const struct pwm_dt_spec pwm_lcd_backlight = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));

static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (button_read(BUTTON_1)) {
        data->key = LV_KEY_LEFT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_1;
    } else if (button_read(BUTTON_2)) {
        data->key = LV_KEY_ENTER;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_2;
    } else if (button_read(BUTTON_3)) {
        data->key = LV_KEY_RIGHT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_3;
    } else {
        if (last_pressed == 0xFF) {
            return;
        }
        data->state = LV_INDEV_STATE_REL;
        switch (last_pressed) {
            case BUTTON_1:
                data->key = LV_KEY_LEFT;
                break;
            case BUTTON_2:
                data->key = LV_KEY_ENTER;
                break; 
            case BUTTON_3:
                data->key = LV_KEY_RIGHT;
                break;            
        }
        last_pressed = 0xFF;
    }
}

static void onButtonPressCb(buttonPressType_t type, buttonId_t id)
{
    LOG_INF("Pressed %d, type: %d", id, type);    
}

void main(void)
{
	const struct device *display_dev;

	if (!device_is_ready(pwm_lcd_backlight.dev)) {
		printk("Error: PWM device %s is not ready\n", pwm_lcd_backlight.dev->name);
		return;
	}	
	
    pwm_set_dt(&pwm_lcd_backlight, input_period, input_period*pwm_duty_cycle/100); 

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return;
	}

	buttonsInit(&onButtonPressCb);

	lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = enocoder_read;
    enc_indev = lv_indev_drv_register(&enc_drv);

    input_group = lv_group_create();
    lv_group_set_default(input_group);
    lv_indev_set_group(enc_indev, input_group);

	ui_init();

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {		
		lv_task_handler();
		k_sleep(K_MSEC(30));
	}
}
