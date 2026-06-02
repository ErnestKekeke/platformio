#include <Arduino.h>
#include <ESP32Servo.h>

#define PIN_SERVO 4

Servo myServo;

void setup(){
  Serial.begin(115200);
  myServo.attach(PIN_SERVO);
}


void loop(){
  myServo.write(0);   // Move to 0 degrees
  Serial.println("Move to 0 degrees");
  delay(1000);

  myServo.write(90);   // Move to 90 degrees
  Serial.println("Move to 90 degrees");
  delay(1000);

  myServo.write(180);   // Move to 180 degrees
  Serial.println("Move to 180 degrees");
  delay(1000);
}