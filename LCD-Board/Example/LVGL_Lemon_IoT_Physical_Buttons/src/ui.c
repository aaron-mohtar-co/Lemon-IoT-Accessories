// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project_Lemon

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1_Panel1;
void ui_event_Screen1_Button1(lv_event_t * e);
lv_obj_t * ui_Screen1_Button1;
lv_obj_t * ui_Screen1_Label1;
void ui_event_Screen1_Button2(lv_event_t * e);
lv_obj_t * ui_Screen1_Button2;
lv_obj_t * ui_Screen1_Label2;
void ui_event_Screen1_Button3(lv_event_t * e);
lv_obj_t * ui_Screen1_Button3;
lv_obj_t * ui_Screen1_Label3;
lv_obj_t * ui_Screen1_Label4;
lv_obj_t * ui_Screen1_Image1;
lv_obj_t * ui_Screen1_Image2;

///////////////////// CALLBACKS ////////////////////
void button1_cb(lv_event_t * e)
{
	
    lv_label_set_text(ui_Screen1_Label4, "Button 1 Click");
}

void button2_cb(lv_event_t * e)
{
	lv_label_set_text(ui_Screen1_Label4, "Button 2 Click");
}

void button3_cb(lv_event_t * e)
{
	lv_label_set_text(ui_Screen1_Label4, "Button 3 Click");
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen1_Button1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        button1_cb(e);
        (e);
    }
}
void ui_event_Screen1_Button2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        button2_cb(e);
        (e);
    }
}
void ui_event_Screen1_Button3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        button3_cb(e);
        (e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Panel1, 320);
    lv_obj_set_height(ui_Screen1_Panel1, 170);
    lv_obj_set_align(ui_Screen1_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Screen1_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Button1 = lv_btn_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Button1, 50);
    lv_obj_set_height(ui_Screen1_Button1, 50);
    lv_obj_set_x(ui_Screen1_Button1, 130);
    lv_obj_set_y(ui_Screen1_Button1, 55);
    lv_obj_set_align(ui_Screen1_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen1_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label1 = lv_label_create(ui_Screen1_Button1);
    lv_obj_set_width(ui_Screen1_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label1, "1");

    ui_Screen1_Button2 = lv_btn_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Button2, 50);
    lv_obj_set_height(ui_Screen1_Button2, 50);
    lv_obj_set_x(ui_Screen1_Button2, 130);
    lv_obj_set_y(ui_Screen1_Button2, 0);
    lv_obj_set_align(ui_Screen1_Button2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen1_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Button2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label2 = lv_label_create(ui_Screen1_Button2);
    lv_obj_set_width(ui_Screen1_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label2, "2");

    ui_Screen1_Button3 = lv_btn_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Button3, 50);
    lv_obj_set_height(ui_Screen1_Button3, 50);
    lv_obj_set_x(ui_Screen1_Button3, 130);
    lv_obj_set_y(ui_Screen1_Button3, -55);
    lv_obj_set_align(ui_Screen1_Button3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen1_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Button3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label3 = lv_label_create(ui_Screen1_Button3);
    lv_obj_set_width(ui_Screen1_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label3, "3");

    ui_Screen1_Label4 = lv_label_create(ui_Screen1_Panel1);
    lv_obj_set_width(ui_Screen1_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label4, -34);
    lv_obj_set_y(ui_Screen1_Label4, -67);
    lv_obj_set_align(ui_Screen1_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label4, "Choose a Button and Press Enter");
    lv_obj_set_style_text_align(ui_Screen1_Label4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Image1 = lv_img_create(ui_Screen1_Panel1);
    lv_img_set_src(ui_Screen1_Image1, &ui_img_1427420713);
    lv_obj_set_width(ui_Screen1_Image1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Image1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Image1, 32);
    lv_obj_set_y(ui_Screen1_Image1, 0);
    lv_obj_set_align(ui_Screen1_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen1_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Screen1_Image1, 200);

    ui_Screen1_Image2 = lv_img_create(ui_Screen1_Panel1);
    lv_img_set_src(ui_Screen1_Image2, &ui_img_225602789);
    lv_obj_set_width(ui_Screen1_Image2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Image2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Image2, -90);
    lv_obj_set_y(ui_Screen1_Image2, 0);
    lv_obj_set_align(ui_Screen1_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Screen1_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Screen1_Image2, 110);

    lv_obj_add_event_cb(ui_Screen1_Button1, ui_event_Screen1_Button1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen1_Button2, ui_event_Screen1_Button2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen1_Button3, ui_event_Screen1_Button3, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}