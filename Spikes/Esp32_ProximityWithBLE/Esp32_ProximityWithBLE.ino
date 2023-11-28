#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAddress.h>

// #include "string.h"

/**
Source: https://youtu.be/azT2rosEo0k
*/

#define LED_PIN 19
#define CUT_OFF -40

void setup() {
  pinMode(LED_PIN, OUTPUT);
  BLEDevice::init("");

  Serial.begin(115200);
}

void loop() {
  BLEScan* scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults allBleDevices = scan->start(1);
  int bestReading = CUT_OFF;

  Serial.print("Number of BLE Devices nearby: ");
  Serial.println(allBleDevices.getCount());

  int maxSignalStrength = 100;
  for (int i = 0; i < allBleDevices.getCount(); i++) {
    BLEAdvertisedDevice device = allBleDevices.getDevice(i);

    // Serial.print("Names of Devices: ");
    // std::string name =  device.getName();
    // Serial.println(name.c_str());

    int rssi = device.getRSSI();

    if (maxSignalStrength > 0) {
      maxSignalStrength = rssi;
    } else {
      if (rssi > maxSignalStrength) {
        maxSignalStrength = rssi;
      }
    }
  }

  Serial.print("Best Signal: ");
  Serial.println(maxSignalStrength);

  digitalWrite(
    LED_PIN,
    maxSignalStrength > CUT_OFF ? HIGH : LOW
  );
  Serial.println("------------------------------------");
}