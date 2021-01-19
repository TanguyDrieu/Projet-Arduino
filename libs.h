#ifndef LIBS_H
#define LIBS_H

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"

#include <couleurs.h>
#include <parametre.h>
#include <variables.h>

// CAPTEURS
Adafruit_BME280 bme;
RTC_DS1307 rtc;
File sdcard_file;

String VERSION = "1.0";
String jSEMAINE = "MON";

#endif