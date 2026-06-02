// RSSI RangeQuality
// -30 to -50 dBmExcellent
// -50 to -70 dBmGood
// -70 to -80 dBmFair
// -80 to -90 dBmWeak 
// Below -90 dBmVery Weak

// WiFi.mode(WIFI_AP);   //  Access Point (Server/Host)
// WiFi.mode(WIFI_STA);  // Station (Client)
// WiFi.mode(WIFI_AP_STA); //  Both AP and Client at same time
// WiFi.mode(WIFI_OFF);  // Turn WiFi off

#include <Arduino.h>
#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);  // Set as client
  WiFi.disconnect();    // Start fresh — no old connections or credentials
  delay(500);           // Give ESP32 time to fully reset WiFi state

  Serial.println("ESP32 WiFi Scanner Ready");
}

void loop() {
  Serial.println("...... Scanning for available Networks ......");

  int numNetworks = WiFi.scanNetworks(); 

  if (numNetworks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println(String(numNetworks) + " network(s) found!");

    for (int i = 0; i < numNetworks; i++) {
      Serial.printf("[%d] %-32s | RSSI: %4d dBm | %s\n",
        i + 1,
        WiFi.SSID(i).c_str(),
        WiFi.RSSI(i),
        (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "OPEN" : "SECURED"
      );
      delay(10);  // 10ms is enough
    }
  }

  WiFi.scanDelete();   // Free memory after scan

  Serial.println("\n........................................\n");
  delay(5000);
}