#include <Arduino.h>
#include <Wire.h>

// Audio and sd card
#include "Audio.h"
#include "SD.h"
#include "SPI.h"
#include "FS.h"

// Digital I/O used
#define I2S_DOUT      17
#define I2S_BCLK      0
#define I2S_LRC       18
#define SD_CS_PIN     10

Audio audio;