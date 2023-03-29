// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project_Lemon

#ifndef _SQUARELINE_PROJECT_LEMON_UI_H
#define _SQUARELINE_PROJECT_LEMON_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Screen1_Panel1;
void ui_event_Screen1_Button1(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Button1;
extern lv_obj_t * ui_Screen1_Label1;
void ui_event_Screen1_Button2(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Button2;
extern lv_obj_t * ui_Screen1_Label2;
void ui_event_Screen1_Button3(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Button3;
extern lv_obj_t * ui_Screen1_Label3;
extern lv_obj_t * ui_Screen1_Label4;
extern lv_obj_t * ui_Screen1_Image1;
extern lv_obj_t * ui_Screen1_Image2;

void button1_cb(lv_event_t * e);
void button2_cb(lv_event_t * e);
void button3_cb(lv_event_t * e);

LV_IMG_DECLARE(ui_img_1427420713);    // assets\Color_circle_(RGB).svg (1).png
LV_IMG_DECLARE(ui_img_225602789);    // assets\LMN v1.1 SM2 (inverted).png



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
