#include <Arduino.h>

int count1;
int count2;

// task 1
void task1(void * parameters){
  Serial.println("initialize any setup for task 1");
  count1 = 0;

  while (true){
    // Serial.println("Task 1 running on core " + String(xPortGetCoreID()));
    Serial.print("count1: ");
    Serial.println(count1);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay 1secs
    count1++;
  }
}

// task2
void task2(void * parameters){
  Serial.println("initialize any setup for task 2");
  count2 = 0;

  while (true){
    // Serial.println("Task 2 running on core " + String(xPortGetCoreID()));
    Serial.print("count2: ");
    Serial.println(count2);
    vTaskDelay(500 / portTICK_PERIOD_MS); // delay 0.5secs
    count2++;
  }
}


void setup(){
  Serial.begin(115200);
  delay(1000); // give Serial time to initialize

  // Create task 1     // xTaskCreatePinnedToCore // 
  xTaskCreate(
    task1,    // function name
    "Task1",  // task name
    2048,     //stack size
    NULL,     // task parameters
    1,        // task priority
    NULL      // task handle
  );

  // Create task 2     // xTaskCreatePinnedToCore // 
  xTaskCreate(
    task2,    // function name
    "Task2",  // task name
    2048,     //stack size
    NULL,     // task parameters
    1,        // task priority
    NULL     // task handle
  );

}

void loop(){
 // Empty (FreeRTOS handles everything)
}