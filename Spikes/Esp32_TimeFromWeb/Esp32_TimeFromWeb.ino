#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>  // 2.13" b/w 128x250, SSD1680, TTGO T5 V2.4.1, V2.3.1

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/17, /*RST=*/16);  // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/16, /*BUSY=*/4);         // arbitrary selection of (16), 4

#include <WiFi.h>
#include "time.h"

const char* ssid = "MEO-DD61C0";
const char* password = "3b2eb46012";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

struct tm printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
  }
  return timeinfo;
}

void printStringToScreen(char* string) {
  display.setRotation(1);
  display.setFont(&FreeMonoBold24pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(string, 0, 0, &tbx, &tby, &tbw, &tbh);

  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;

  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.print(string);
  display.update();
}

void setup() {
  Serial.begin(115200);

  /*
  Wifi
  */
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  /*
  Display
  */
  display.init(115200);  // enable diagnostic output on Serial
}

int oldMinute = 1000;
char buffer[100];

void loop() {
  struct tm timeinfo = printLocalTime();
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  int hour = timeinfo.tm_hour;
  int min = timeinfo.tm_min;

  if (min != oldMinute) {
    oldMinute = min;
    if (min < 10)
    {
      snprintf(buffer, 100, "%d:0%d", hour, min);
    } else {
      snprintf(buffer, 100, "%d:%d", hour, min);
    }
    printStringToScreen(buffer);
  }
  delay(1000);
  // display.powerDown();
};
