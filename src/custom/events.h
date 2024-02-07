#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

#include "ui/ui.h"
#include "gui/gui.h"
#include "global_variables.h"

int brightness_address = 0;
int sound_address = 5;

int brightness_val = 50;
int sound_val = 10;

uint updateSetting_delay = 0;
bool updateBrightness = false;
bool updateSoundVolumn = false;

// Setup the brightness and sound
void updateSetting() {
  if(millis() - updateSetting_delay >= 500 && updateBrightness) {
    EEPROM.writeUInt(brightness_address, brightness_val);
    EEPROM.commit();
    updateBrightness = false;
    Serial.printf("Update brightness: %d\n", brightness_val);
  }

  if(millis() - updateSetting_delay >= 500 && updateSoundVolumn) {
    EEPROM.writeUInt(sound_address, sound_val);
    EEPROM.commit();
    updateSoundVolumn = false;
    Serial.printf("Update Volume: %d\n", sound_val);
  }
}

void setBrightness(lv_event_t * e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(event_code == LV_EVENT_VALUE_CHANGED) {
      updateSetting_delay = millis();
      updateBrightness = true;
      brightness_val = lv_slider_get_value(target);
      Serial.printf("Brightness: %d\n", brightness_val);
      gfx.setBrightness(brightness_val);
  }
}

void setSoundVolumn(lv_event_t * e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(event_code == LV_EVENT_VALUE_CHANGED) {
      sound_val = lv_slider_get_value(target);
      updateSetting_delay = millis();
      updateSoundVolumn = true;
      audio.setVolume(sound_val); // 0...21
      Serial.printf("Volume: %d\n", sound_val);
  }
}

///////////////////// VARIABLES ////////////////////
const char thicknessNumber = 10; 
float thickness[thicknessNumber];
int current_ui_index;

// Match ui_index to ui_Thickness
lv_obj_t *ui_Thickness(int ui_index) {
   switch (ui_index) {
        case 0:
            return ui_Thickness1;
        case 1:
            return ui_Thickness2;
        case 2:
            return ui_Thickness3;
        case 3:
            return ui_Thickness4;
        case 4:
            return ui_Thickness5;
        case 5:
            return ui_Thickness6;
        case 6:
            return ui_Thickness7;
        case 7:
            return ui_Thickness8;
        case 8:
            return ui_Thickness9;
        case 9:
            return ui_Thickness10;
        default:
            // กรณีนี้คือ index ไม่ถูกต้อง
            printf("Invalid index\n");
            return NULL; // หรือให้รีเทิร์นค่าที่เหมาะสมตามที่คุณต้องการ
    }
};

void ui_event_ThicknessPanel(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        // ดึงค่าที่ถูกส่งมาจาก user_data
        int _ui_index = (int)lv_event_get_user_data(e);
        // ใช้ค่าที่ถูกส่งมาใน custom_value
        String placeholder = "Tablet number " + String(_ui_index + 1);
        lv_textarea_set_placeholder_text(ui_ThicknessValue, placeholder.c_str());
        _ui_flag_modify(ui_KeyboardPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        current_ui_index = _ui_index;
    }
}

void ui_event_ThicknessKeyboard(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_READY) {
        char value_char[6];
        float value = atof(lv_textarea_get_text(ui_ThicknessValue));

        if(value) {
          thickness[current_ui_index] = value;
          sprintf(value_char, "%.2f", value);
          lv_label_set_text(ui_Thickness(current_ui_index), value_char);
          _ui_flag_modify(ui_KeyboardPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
          lv_textarea_set_text(ui_ThicknessValue, "");
          
          bool flag = false;
          for(int i = 0; i < thicknessNumber; i++) {
              if(thickness[i] > 0){
                  flag = true;
              } else {
                  flag = false;
                  break;
              }
          }

          if(flag) {
              _ui_state_modify(ui_ConfirmBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_REMOVE);
          } else {
              _ui_state_modify(ui_ConfirmBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
          }
        }
    }
}

void ui_event_ThicknessMainPanel(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(ui_ThicknessValue, "");
        _ui_flag_modify(ui_KeyboardPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_ConfirmBTN(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        DynamicJsonDocument doc(200);
        JsonArray thicknessArray = doc.createNestedArray("thickness");

        for (int i = 0; i < thicknessNumber; i++) {
            String formattedValue = String(thickness[i], 2);
            thicknessArray.add(formattedValue);
        }

        String jsonString;
        serializeJson(doc, jsonString);
        Serial.println(jsonString);
    }
}

// Event connect to wifi
String ssid, password;
void wifi_signal(String ssid) {
    for (JsonObject obj : wifi_cache["wifi"].as<JsonArray>()) {
        String _ssid = obj["SSID"].as<String>();
        if (ssid == _ssid) {
            int signal_strength = obj["Signal_Strength"].as<int>();
            lv_bar_set_value(ui_WifiSignal, signal_strength, LV_ANIM_OFF);
            break;
        }

        lv_bar_set_value(ui_WifiSignal, -100, LV_ANIM_OFF);
    }
}

void ui_event_Setting(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_dropdown_set_options(ui_WifiList, "");
        lv_bar_set_value(ui_WifiSignal, -100, LV_ANIM_OFF);
        _ui_state_modify(ui_WifiConnectBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
        _ui_screen_change(&ui_SettingPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_SettingPage_screen_init);
    }
}

void ui_event_WifiScanBtn(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        lv_dropdown_set_options(ui_WifiList, "");
        lv_bar_set_value(ui_WifiSignal, -150, LV_ANIM_OFF);
        _ui_state_modify(ui_WifiConnectBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
        _ui_flag_modify(ui_WaitingToWifi, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        DynamicJsonDocument doc(50);
        doc["WiFi"] = "Scan";
        String jsonString;
        serializeJson(doc, jsonString);
        Serial.println(jsonString);
        wifi_scan_timeout = millis();
    }
}

void ui_event_WifiList(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t * dropdown = lv_event_get_target(e);
        char buf[30];
        lv_dropdown_get_selected_str(dropdown, buf, sizeof(buf));
        ssid = String(buf);
        wifi_signal(ssid);
        Serial.printf("'%s' is selected\n", buf);
    }
}

void ui_event_WifiConnectBtn(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_textarea_set_text(ui_WifiKeboardInput, "");
        _ui_flag_modify(ui_WifiKeyboardPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

void ui_event_WifiKeyboard(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_READY) {
        String password_val = String(lv_textarea_get_text(ui_WifiKeboardInput));
        if(password_val != "null") {
            _ui_flag_modify(ui_WifiKeyboardPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
            password = password_val;
            DynamicJsonDocument doc(50);
            doc["WiFi"] = "connect";
            doc["ssid"] = ssid;
            doc["password"] = password;

            // แปลง JSON object เป็น String
            String jsonString;
            serializeJson(doc, jsonString);
            Serial.println(jsonString);
        }
    }
}

// Add all events
void addEvents() {
    lv_slider_set_value(ui_Sound, sound_val, LV_ANIM_OFF);
    lv_slider_set_value(ui_Brightness, brightness_val, LV_ANIM_OFF);
    lv_obj_add_event_cb(ui_Brightness, setBrightness, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Sound, setSoundVolumn, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_WifiScanBtn, ui_event_WifiScanBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiList, ui_event_WifiList, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiConnectBtn, ui_event_WifiConnectBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiKeyboard, ui_event_WifiKeyboard, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_SettingBtn, ui_event_Setting, LV_EVENT_ALL, NULL);

    // Event enter the tablet thickness value.
    lv_obj_add_event_cb(ui_ThicknessMainPanel, ui_event_ThicknessMainPanel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ThicknessKeyboard, ui_event_ThicknessKeyboard, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ConfirmBtn, ui_event_ConfirmBTN, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_ThicknessPanel1, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)0);
    lv_obj_add_event_cb(ui_ThicknessPanel2, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)1);
    lv_obj_add_event_cb(ui_ThicknessPanel3, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)2);
    lv_obj_add_event_cb(ui_ThicknessPanel4, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)3);
    lv_obj_add_event_cb(ui_ThicknessPanel5, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)4);
    lv_obj_add_event_cb(ui_ThicknessPanel6, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)5);
    lv_obj_add_event_cb(ui_ThicknessPanel7, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)6);
    lv_obj_add_event_cb(ui_ThicknessPanel8, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)7);
    lv_obj_add_event_cb(ui_ThicknessPanel9, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)8);
    lv_obj_add_event_cb(ui_ThicknessPanel10, ui_event_ThicknessPanel, LV_EVENT_ALL, (void *)9);

}