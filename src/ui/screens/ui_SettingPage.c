// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Weight

#include "../ui.h"

void ui_SettingPage_screen_init(void)
{
    ui_SettingPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Brightness = lv_slider_create(ui_SettingPage);
    lv_slider_set_range(ui_Brightness, 50, 127);
    lv_obj_set_width(ui_Brightness, 230);
    lv_obj_set_height(ui_Brightness, 10);
    lv_obj_set_x(ui_Brightness, -220);
    lv_obj_set_y(ui_Brightness, -190);
    lv_obj_set_align(ui_Brightness, LV_ALIGN_CENTER);


    ui_BrightnessLabel = lv_label_create(ui_SettingPage);
    lv_obj_set_width(ui_BrightnessLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BrightnessLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BrightnessLabel, -225);
    lv_obj_set_y(ui_BrightnessLabel, -215);
    lv_obj_set_align(ui_BrightnessLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BrightnessLabel, "Brightness");
    lv_obj_set_style_text_color(ui_BrightnessLabel, lv_color_hex(0x494949), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BrightnessLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Sound = lv_slider_create(ui_SettingPage);
    lv_slider_set_range(ui_Sound, 0, 21);
    lv_obj_set_width(ui_Sound, 230);
    lv_obj_set_height(ui_Sound, 10);
    lv_obj_set_x(ui_Sound, 220);
    lv_obj_set_y(ui_Sound, -190);
    lv_obj_set_align(ui_Sound, LV_ALIGN_CENTER);


    ui_SoundLabel = lv_label_create(ui_SettingPage);
    lv_obj_set_width(ui_SoundLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SoundLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SoundLabel, 225);
    lv_obj_set_y(ui_SoundLabel, -215);
    lv_obj_set_align(ui_SoundLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SoundLabel, "Sound");
    lv_obj_set_style_text_color(ui_SoundLabel, lv_color_hex(0x494949), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SoundLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiPanel = lv_obj_create(ui_SettingPage);
    lv_obj_set_width(ui_WifiPanel, 751);
    lv_obj_set_height(ui_WifiPanel, 379);
    lv_obj_set_x(ui_WifiPanel, 0);
    lv_obj_set_y(ui_WifiPanel, 30);
    lv_obj_set_align(ui_WifiPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_WifiPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_shadow_color(ui_WifiPanel, lv_color_hex(0x262626), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_WifiPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_WifiPanel, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_WifiPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_WifiPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_WifiPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiScanBtn = lv_btn_create(ui_WifiPanel);
    lv_obj_set_width(ui_WifiScanBtn, 150);
    lv_obj_set_height(ui_WifiScanBtn, 45);
    lv_obj_set_x(ui_WifiScanBtn, -230);
    lv_obj_set_y(ui_WifiScanBtn, -140);
    lv_obj_set_align(ui_WifiScanBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiScanBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiScanBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WifiScanLabel = lv_label_create(ui_WifiScanBtn);
    lv_obj_set_width(ui_WifiScanLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WifiScanLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_WifiScanLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WifiScanLabel, "WIFI SCAN");
    lv_obj_set_style_text_font(ui_WifiScanLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiList = lv_dropdown_create(ui_WifiPanel);
    lv_dropdown_set_options(ui_WifiList, "WIFI_1\nWIFI_2\nWIFI_3");
    lv_obj_set_width(ui_WifiList, 486);
    lv_obj_set_height(ui_WifiList, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WifiList, -60);
    lv_obj_set_y(ui_WifiList, -70);
    lv_obj_set_align(ui_WifiList, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiList, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags



    ui_WifiSignal = lv_bar_create(ui_WifiList);
    lv_bar_set_range(ui_WifiSignal, -100, -30);
    lv_bar_set_value(ui_WifiSignal, -100, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_WifiSignal, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_WifiSignal, 168);
    lv_obj_set_height(ui_WifiSignal, 18);
    lv_obj_set_x(ui_WifiSignal, 108);
    lv_obj_set_y(ui_WifiSignal, 0);
    lv_obj_set_align(ui_WifiSignal, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_WifiSignal, lv_color_hex(0xFC7600), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiSignal, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_WifiSignal, lv_color_hex(0x3CF200), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_WifiSignal, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_WifiConnectBtn = lv_btn_create(ui_WifiPanel);
    lv_obj_set_width(ui_WifiConnectBtn, 100);
    lv_obj_set_height(ui_WifiConnectBtn, 42);
    lv_obj_set_x(ui_WifiConnectBtn, 253);
    lv_obj_set_y(ui_WifiConnectBtn, -70);
    lv_obj_set_align(ui_WifiConnectBtn, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_WifiConnectBtn, LV_STATE_DISABLED);       /// States
    lv_obj_add_flag(ui_WifiConnectBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiConnectBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WifiConnectLabel = lv_label_create(ui_WifiConnectBtn);
    lv_obj_set_width(ui_WifiConnectLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WifiConnectLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_WifiConnectLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WifiConnectLabel, "Connect");

    ui_CloseSettingBtn = lv_btn_create(ui_WifiPanel);
    lv_obj_set_width(ui_CloseSettingBtn, 150);
    lv_obj_set_height(ui_CloseSettingBtn, 45);
    lv_obj_set_x(ui_CloseSettingBtn, -70);
    lv_obj_set_y(ui_CloseSettingBtn, -140);
    lv_obj_set_align(ui_CloseSettingBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CloseSettingBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CloseSettingBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_CloseSettingBtn, lv_color_hex(0xFF0303), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CloseSettingBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_CloseSettingBtn, lv_color_hex(0xFA5D5D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CloseSettingBtn, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CloseSettingLabel = lv_label_create(ui_CloseSettingBtn);
    lv_obj_set_width(ui_CloseSettingLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CloseSettingLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_CloseSettingLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CloseSettingLabel, "CLOSE");
    lv_obj_set_style_text_font(ui_CloseSettingLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WaitingToWifi = lv_obj_create(ui_SettingPage);
    lv_obj_set_width(ui_WaitingToWifi, 751);
    lv_obj_set_height(ui_WaitingToWifi, 379);
    lv_obj_set_x(ui_WaitingToWifi, 0);
    lv_obj_set_y(ui_WaitingToWifi, 30);
    lv_obj_set_align(ui_WaitingToWifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WaitingToWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_WaitingToWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_WaitingToWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WaitingToWifi, 200, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiSpinner = lv_spinner_create(ui_WaitingToWifi, 1000, 90);
    lv_obj_set_width(ui_WifiSpinner, 201);
    lv_obj_set_height(ui_WifiSpinner, 204);
    lv_obj_set_align(ui_WifiSpinner, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_WifiSpinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_WifiSpinner, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiKeyboardPanel = lv_obj_create(ui_SettingPage);
    lv_obj_set_width(ui_WifiKeyboardPanel, 801);
    lv_obj_set_height(ui_WifiKeyboardPanel, 302);
    lv_obj_set_x(ui_WifiKeyboardPanel, 0);
    lv_obj_set_y(ui_WifiKeyboardPanel, 87);
    lv_obj_set_align(ui_WifiKeyboardPanel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiKeyboardPanel, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_WifiKeyboardPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WifiKeyboard = lv_keyboard_create(ui_WifiKeyboardPanel);
    lv_obj_set_width(ui_WifiKeyboard, 796);
    lv_obj_set_height(ui_WifiKeyboard, 239);
    lv_obj_set_x(ui_WifiKeyboard, 0);
    lv_obj_set_y(ui_WifiKeyboard, 32);
    lv_obj_set_align(ui_WifiKeyboard, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_WifiKeyboard, lv_color_hex(0xA4D0FE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiKeyboard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiKeboardInput = lv_textarea_create(ui_WifiKeyboardPanel);
    lv_obj_set_width(ui_WifiKeboardInput, 653);
    lv_obj_set_height(ui_WifiKeboardInput, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_WifiKeboardInput, 0);
    lv_obj_set_y(ui_WifiKeboardInput, -116);
    lv_obj_set_align(ui_WifiKeboardInput, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_WifiKeboardInput, 50);
    lv_textarea_set_placeholder_text(ui_WifiKeboardInput, "Password...");
    lv_textarea_set_one_line(ui_WifiKeboardInput, true);



    lv_obj_add_event_cb(ui_CloseSettingBtn, ui_event_CloseSettingBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiPanel, ui_event_WifiPanel, LV_EVENT_ALL, NULL);
    lv_keyboard_set_textarea(ui_WifiKeyboard, ui_WifiKeboardInput);

}
