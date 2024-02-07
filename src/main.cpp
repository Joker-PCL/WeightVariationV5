#include <Arduino.h>
#include <EEPROM.h>
// #include <WiFi.h>
#include <lv_conf.h>
#include <lvgl.h>

#include "custom/sd_audio.h"
#include "custom/events.h"
#include "custom/connectRPi.h"

#define LV_LOG_LEVEL_TRACE

TaskHandle_t TaskAudio;

ulong previousTimeA = 0;
ulong previousTimeB = 0;
int delay_millis = 0;

bool Start = false;
bool loadingPage = true;
void performance() {
    if (millis() - previousTimeB > 1000) {
      Serial.printf("Total heap: %d\n", ESP.getHeapSize());
      Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
      Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
      Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
      previousTimeB = millis();
    }
}

void audioLoop(void * val) {
  for(;;) {
    audio.loop();
    // performance();
  }
}

void lv_log_to_sd(const char * buf)
{
  // เปิดไฟล์เพื่อเขียนข้อมูล log
  File logFile = SD.open("lvgl_log.txt", FILE_WRITE);
  
  // ตรวจสอบว่าไฟล์เปิดได้หรือไม่
  if (logFile)
  {
    // เขียนข้อความ log ลงในไฟล์
    logFile.println(buf);
    // ปิดไฟล์
    logFile.close();
  }
  else
  {
    // แสดงข้อความเตือนหากไม่สามารถเปิดไฟล์ได้
    Serial.println("Error opening lvgl_log.txt");
  }
}

void setup() {
  EEPROM.begin(50);
  Serial.begin(115200);

  brightness_val = EEPROM.readUInt(brightness_address);
  brightness_val < 50 || brightness_val > 127 ? 50 : brightness_val;

  sound_val = EEPROM.readUInt(sound_address);
  sound_val < 0 || sound_val > 21 ? 21 : sound_val;
      Serial.printf("Volume: %d\n", sound_val);

  // WiFi.begin(ssid1, password1);
  // configTime(UTC_OFFSET_SECONDS, UTC_OFFSET_DST, NTP_SERVER);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(sound_val); // 0...21
  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
      Serial.println("Error initializing SD card!");
      while (1);
  }

  gui_start();
  gfx.setBrightness(brightness_val);

  addEvents();
  lv_log_register_print_cb(lv_log_to_sd);
  xTaskCreatePinnedToCore(audioLoop, "TaskAudio", 5000, NULL, 9, &TaskAudio, 0);
}

int sounds = 1;
void loop() {
  lv_timer_handler();
  delay(5);

  if (millis() - previousTimeA > 5000) {
    previousTimeA = millis();
    // wifiConnect();

    // Specify the path to your MP3 file on the SD card
    String music_path = "/Sounds/Sound" + String(sounds) +".mp3";
    audio.connecttoSD(music_path.c_str());
    if(sounds < 4)
      sounds++;
    else
      sounds = 1;
  }

  if (millis() - delay_millis >= 500) {
    // printLocalTime();
    delay_millis = millis();

    char charFloat[10]; // กำหนดขนาดของ char array ตามต้องการ
    float weight1 = random(50, 80) / 100.000;
    float weight2 = random(50, 80) / 100.000;
    float average = (weight1 + weight2) / 2;

    dtostrf(weight1, 6, 3, charFloat);
    lv_label_set_text(ui_Weight1, charFloat);
    dtostrf(weight2, 6, 3, charFloat);
    lv_label_set_text(ui_Weight2, charFloat);
    dtostrf(average, 6, 3, charFloat);
    lv_label_set_text(ui_Average, charFloat);
  }

  updateSetting();
  connectToRaspberryPi();
}
