#include <Arduino.h>

TaskHandle_t task1_handle = NULL;

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

    if(count1 == 3){
      Serial.println("Task 1 suspending itself");
      vTaskSuspend(NULL); 
      // vTaskDelete(NULL);
    }
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


// Just for reference when working with inportant task
void superImportantTask(){

  vTaskSuspendAll(); //  including the void loop

  // Run critical mission code
  
  xTaskResumeAll();
}


void setup(){
  Serial.begin(115200);
  delay(1000); // give Serial time to initialize

  xTaskCreate(task1, "Task1", 2048, NULL, 1, &task1_handle);
  xTaskCreate(task2, "Task2", 2048, NULL, 1, NULL);
}

void loop(){
  // Resume task1 only once when condition is met
  if(count2 == 20 && task1_handle != NULL){
    Serial.println("Resuming Task 1");

    vTaskResume(task1_handle);

    task1_handle = NULL;  // prevent repeated resumes
  }
}