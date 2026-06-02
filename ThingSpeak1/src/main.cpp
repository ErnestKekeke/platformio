#include <Arduino.h>
#include <WiFi.h>
#include "ThingSpeak.h"

unsigned long CHANNEL_ID  = 3361229;
const char * CHANNEL_WRITE_API_KEY = "7MA5HP5QUYVK9WZH";

WiFiClient client;

const char* SSID = "Kkk A17";
const char* PASSWORD = "77654321";

void connect_to_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  connect_to_wifi();

  ThingSpeak.begin(client);
  delay(15000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    int numRandom1 = random(0, 100);
    int numRandom2 = random(0, 100);
    Serial.println(numRandom1);
    Serial.println(numRandom2);

    // send Data to Single feild
    // ThingSpeak.writeField(CHANNEL_ID, 1, numRandom1, CHANNEL_WRITE_API_KEY);
   

    // Send Data to Multiple Feilds
    ThingSpeak.setField(1, numRandom1);
    ThingSpeak.setField(2, numRandom2);

    // ThingSpeak.writeFields(CHANNEL_ID,  CHANNEL_WRITE_API_KEY);
    int response = ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_WRITE_API_KEY);
    if (response == 200) {
        Serial.println("Channel update successful.");
    } else {
        Serial.print("Problem updating channel. HTTP error code ");
        Serial.println(response);
    }

    delay(15000);

  } else {
    Serial.println("WiFi lost... waiting for auto-reconnect");
    delay(5000);
  }
}