#include <Arduino.h>
#include "BluetoothAudio.h"
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>
#include <BLEDevice.h>

BluetoothAudio bluetoothAudio;

void setup() {
  Serial.begin(115200);

  // Initialize BT controller in dual mode (Classic + BLE)
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

  esp_err_t ret = esp_bt_controller_init(&bt_cfg);
  if (ret) {
    Serial.printf("Bluetooth controller initialize failed: %s\n", esp_err_to_name(ret));
    return;
  }

  ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
  if (ret) {
    Serial.printf("Bluetooth controller enable failed: %s\n", esp_err_to_name(ret));
    return;
  }

  ret = esp_bluedroid_init();
  if (ret) {
    Serial.printf("Bluedroid stack init failed: %s\n", esp_err_to_name(ret));
    return;
  }

  ret = esp_bluedroid_enable();
  if (ret) {
    Serial.printf("Bluedroid stack enable failed: %s\n", esp_err_to_name(ret));
    return;
  }

  // Initialize BLE device after BT controller is enabled
  BLEDevice::init("ESP32-iPod-Emu");

  // TODO: initialize your BLE services & callbacks here, e.g.
  // ble_server_init();

  // Start A2DP Sink audio
  bluetoothAudio.start();
}

void loop() {
  // Your main loop logic here
}
