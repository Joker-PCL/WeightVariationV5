#include <Arduino.h>
#include <ArduinoJson.h>
#include <time.h>

#include "../ui/ui.h"
#include "pages_onload/login_page.h"
#include "pages_onload/weighing_page.h"
#include "pages_onload/thickness_page.h"

DynamicJsonDocument rpi_doc(250);

String currentPage = "LoadingPage";
bool change_screen = false;

int screen_server = 10000;
ulong screen_server_millis = 0;

// กำหนดโซนเวลาและเซิร์ฟเวอร์ NTP
// const char *NTP_SERVER = "pool.ntp.org";
// const long UTC_OFFSET_SECONDS = 7 * 3600; // UTC+7 (กรุงเทพ)
// const long UTC_OFFSET_DST = 0; // ไม่มี Daylight Saving Time ในประเทศไทย

void syncTimeFromSerial(String datetime) {
  int year, month, day, hour, minute, second;
  
  if (sscanf(datetime.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
    struct tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;

    // Convert struct tm to time_t
    time_t epoch = mktime(&timeinfo);

    // Set the system time
    struct timeval tv = {.tv_sec = epoch};
    settimeofday(&tv, nullptr);

    DynamicJsonDocument doc(50);
    doc["result"] = "success";

    // แปลง JSON object เป็น String
    String jsonString;
    serializeJson(doc, jsonString);
    Serial.println(jsonString);
  }
}

void createWifiList(DynamicJsonDocument& wifi_list) {
  _ui_flag_modify(ui_WaitingToWifi, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  wifi_cache = wifi_list;
  // สร้างสตริงรายชื่อ SSID
  String ssidList;
  for (JsonObject obj : wifi_list["wifi"].as<JsonArray>()) {
    String ssid = obj["SSID"].as<String>();
    if (!ssid.isEmpty()) { // ตรวจสอบว่า SSID ไม่ว่าง
      ssidList += ssid + "\n";
    }
  }

  if (ssidList.endsWith("\n")) {
    ssidList.remove(ssidList.length() - 1);
  }
  
  if (ssidList != "null"){
    lv_dropdown_set_options(ui_WifiList, ssidList.c_str());
    int signal_strength = wifi_list["Signal_Strength"][0].as<int>();
    lv_bar_set_value(ui_WifiSignal, signal_strength, LV_ANIM_OFF);
    _ui_state_modify(ui_WifiConnectBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_REMOVE);
  } 
  else {
    _ui_state_modify(ui_WifiConnectBtn, LV_STATE_DISABLED, _UI_MODIFY_STATE_ADD);
  }
}

void connectToRaspberryPi() {    
  // check rfid
  if(Serial.available()) {
    String jsonString = Serial.readStringUntil('\n');
    // แปลง JSON string เป็น JSON object
    deserializeJson(rpi_doc, jsonString);
    String datetime = rpi_doc["datetime"];
    String page = rpi_doc["page"];
    String command = rpi_doc["command"];
    String wifi_list = rpi_doc["wifi"];

    if(datetime != "null") {
      syncTimeFromSerial(datetime);
    } else if (wifi_list != "null") {
      createWifiList(rpi_doc);
    } else if (command == "restart") {
      ESP.restart();
    }

    if(page != "null" && currentPage != page) { 
        currentPage = page;
        change_screen = true;
    }
  }

  if(currentPage == "LoginPage") {
    if(change_screen) {
        _ui_screen_change(&ui_LoginPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_LoginPage_screen_init);
    }

    loginPage_init(rpi_doc);
    
  } else if(currentPage == "WeightingPage") {
    if(change_screen) {
      _ui_screen_change(&ui_WeighingPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_WeighingPage_screen_init);
    }
    
    weighingPage_init(rpi_doc);
  }
  else if(currentPage == "ThicknessPage") {
    if(change_screen) {
      _ui_screen_change(&ui_ThicknessPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_ThicknessPage_screen_init);
    }

    thicknessPage_init(rpi_doc);
  }
  else if(currentPage == "TabletCharacteristicsPage") {
    if(change_screen) {
      _ui_screen_change(&ui_TabletCharacteristicsPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_TabletCharacteristicsPage_screen_init);
    }
  }
  else if(currentPage == "SummaryPage") {
    if(change_screen) {
      _ui_screen_change(&ui_SummaryPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_SummaryPage_screen_init);
    }
  }
  else {
    if(change_screen) {
      _ui_screen_change(&ui_LoadingPage, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_LoadingPage_screen_init);
    }
  }

  change_screen = false;
  rpi_doc.clear();

  if(millis() - wifi_scan_timeout >= 6000) {
    _ui_flag_modify(ui_WaitingToWifi, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  }
}
