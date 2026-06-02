#include <Arduino.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "Kkk A17";
const char* password = "77654321";

DHT dht(DHTPIN, DHTTYPE);

float temperature = 0;
float humidity = 0;

// Task 1: Read sensor
void readTask(void *p) {
  while (1) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// Task 2: Print data
void printTask(void *p) {
  while (1) {
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.println(humidity);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task 3: WiFi + send data
void wifiTask(void *p) {
  // Enable auto reconnect
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }

  Serial.println("\nWiFi connected!");

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Sending data over WiFi...");
    } else {
      Serial.println("WiFi lost...");
      // No need to call WiFi.begin() repeatedly anymore
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  delay(1000);

  xTaskCreate(readTask, "Read Sensor", 2000, NULL, 1, NULL);
  xTaskCreate(printTask, "Print Data", 2000, NULL, 1, NULL);
  xTaskCreate(wifiTask, "WiFi Task", 4000, NULL, 1, NULL);
}

void loop() {
  // nothing here
}