#include <Arduino.h>
#include "esp_sleep.h"

#define TOUCH_PIN T0 // (GPIO 4)
#define TOUCH_THRESHOLD 40

// void callback(){}
void IRAM_ATTR callback() {
  // required but unused in deep sleep
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 Touch Wakeup Example");

  // Check wake reason
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  Serial.println(reason);
  Serial.println("...... \n");

  // Configure touch wake-up
  touchAttachInterrupt(TOUCH_PIN, callback, TOUCH_THRESHOLD);
  esp_sleep_enable_touchpad_wakeup();

  Serial.println("Touch to wake device...");

  delay(2000);
  Serial.println("Going to sleep now");

  esp_deep_sleep_start();
}

void loop() {
  // never runs
}