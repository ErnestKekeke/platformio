#include <Arduino.h>
#include "esp_sleep.h"

#define BUTTON_PIN GPIO_NUM_4   // RTC-capable pin

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 EXT0 Wake-up Example");

  // Check wake reason
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  Serial.println(reason);
  Serial.println(".....\n");

  // Configure EXT0 wake-up
  esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 1);
  // 1 = wake when pin is HIGH
  // 0 = wake when pin is LOW

  Serial.println("Press button to wake device...");

  delay(2000);
  Serial.println("Going to sleep now");

  esp_deep_sleep_start();
}

void loop() {
  // It wil Never Run
}