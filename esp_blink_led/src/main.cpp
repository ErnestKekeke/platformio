#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4        // GPIO pin connected to DATA
#define DHTTYPE DHT22   // change to DHT22 if needed

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  ");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(2000); // DHT needs at least 2 seconds between reads
}