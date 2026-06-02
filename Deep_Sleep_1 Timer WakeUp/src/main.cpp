#include <Arduino.h>
#include "esp_sleep.h"

const unsigned int SLEEP_DURATION = 15;

void setup(){
  Serial.begin(115200);

  // Active code, when esp32 is awake from sleep
  Serial.println("Connect to WiFi, if needed");
  Serial.println("Taking Measurement or Do Something");
  Serial.println("Sending Measurement or Do Something if Be...\n");

    // Check wake-up reason
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  Serial.println(reason);
  Serial.println("\n\n");
  // .......
  
  Serial.println("Going to Sleep\n");

  // esp_sleep_enable_timer_wakeup(SLEEP_DURATION * 60 * 1000000); // 15mins
  esp_sleep_enable_timer_wakeup(SLEEP_DURATION * 1000000); // 15secs
  esp_deep_sleep_start();

  // any code here after deep sleep would no run
}

void loop(){
  // no code here 
}