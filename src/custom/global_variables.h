#include <Arduino.h>
#include <ArduinoJson.h>

DynamicJsonDocument wifi_cache(250);

uint wifi_scan_timeout = 0;