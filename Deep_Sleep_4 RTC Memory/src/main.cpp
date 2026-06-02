#include <Arduino.h>
#include "esp_sleep.h"

// Stored in RTC memory → retains value even after deep sleep reset
RTC_DATA_ATTR int count = 0;

// for related data, you can use struct 
struct Data{
  int num;
  char alpha;
};

RTC_DATA_ATTR Data data = {0, 'A'};


void setup() {
  Serial.begin(115200);
  Serial.println("... START PROGRAM ... \n");

  count++;
  Serial.print("count: ");
  Serial.println(count);

  Serial.println("\n ... END PROGRAM ... \n");

  // using timmer as wake up 
  esp_sleep_enable_timer_wakeup(20 * 1000000);  // 20 secs
  esp_deep_sleep_start();
}

void loop(){
  // This will never run
}