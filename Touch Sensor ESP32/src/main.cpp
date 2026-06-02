#include <Arduino.h>

#define WIRE_PAD 4 // Touch pin (T0 on ESP32)

void setup(){
  Serial.begin(115200);
  // pinMode(WIRE_PAD, INPUT); // is not needed (and can cause problems)
}


void loop(){
  // Serial.println(touchRead(WIRE_PAD));
  Serial.println(touchRead(T0));
  delay(200);
}