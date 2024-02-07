#include <Arduino.h>
#include "../../ui/ui.h"

uint refreshTime = 0;
void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Connection Err");
        return;
    }

    if(millis() - refreshTime >= 1000) {
        refreshTime = millis();

        char hoursStr[3];
        char minutesStr[3];
        char secondsStr[3];
        char dateStr[11];

        strftime(hoursStr, sizeof(hoursStr), "%H", &timeinfo);
        strftime(minutesStr, sizeof(minutesStr), "%M", &timeinfo);
        strftime(secondsStr, sizeof(secondsStr), "%S", &timeinfo);
        strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", &timeinfo);

        lv_label_set_text(ui_Hours, hoursStr);     // Display hours
        lv_label_set_text(ui_Minutes, minutesStr); // Display minutes
        lv_label_set_text(ui_Seconds, secondsStr); // Display seconds
        lv_label_set_text(ui_Date, dateStr);       // Display Date

        // Serial.println(&timeinfo, "%d/%m/%Y, %H:%M:%S");
    }
}

int ui_ErrMsgRfidScanTime = 0;
bool ui_ErrMsgRfidScanState = false;

void loginPage_init(DynamicJsonDocument& rpi_doc) {
    String rfid = rpi_doc["rfid"];
        
    if(rfid != "null") {
        lv_label_set_text(ui_RFID, rfid.c_str());
        if(rfid == "1234567890") {
            _ui_screen_change(&ui_WeighingPage, LV_SCR_LOAD_ANIM_FADE_IN, 500, 0, &ui_WeighingPage_screen_init);
            lv_label_set_text(ui_RFID, "XXXXXXXXXX");
        } else {
            lv_obj_add_flag(ui_MsgRfidScan, LV_OBJ_FLAG_HIDDEN);  
            lv_obj_clear_flag(ui_ErrMsgRfidScan, LV_OBJ_FLAG_HIDDEN); 
            ui_ErrMsgRfidScanState = true;
            ui_ErrMsgRfidScanTime = millis();
        }
    }

    if(ui_ErrMsgRfidScanState) {
        if(millis() - ui_ErrMsgRfidScanTime >= 3000) {
            lv_label_set_text(ui_RFID, "XXXXXXXXXX");
            lv_obj_clear_flag(ui_MsgRfidScan, LV_OBJ_FLAG_HIDDEN);  
            lv_obj_add_flag(ui_ErrMsgRfidScan, LV_OBJ_FLAG_HIDDEN); 
            ui_ErrMsgRfidScanState = false;
        }
    }

    printLocalTime();
}