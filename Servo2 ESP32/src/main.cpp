#include <Arduino.h>

// ===== Servo config =====
const int servoPin = 4;     // GPIO pin connected to servo signal
const int servoFreq = 50;    // 50Hz for standard servos
const int resolution = 16;   // 16-bit resolution

const int channel = 0;       // LEDC channel (0–15)

// Pulse range for typical servo (adjust if needed)
const int minPulse = 1638;   // ~0.5 ms
const int maxPulse = 8192;   // ~2.5 ms

// ===== Setup =====
void setup() {
  Serial.begin(115200);

  // Configure PWM channel
  ledcSetup(channel, servoFreq, resolution);
  ledcAttachPin(servoPin, channel);

  Serial.println("Servo ready");
}

// ===== Convert angle to PWM duty =====
void setServoAngle(int angle) {
  angle = constrain(angle, 0, 180);

  int duty = map(angle, 0, 180, minPulse, maxPulse);
  ledcWrite(channel, duty);

  Serial.print("Angle: ");
  Serial.println(angle);
}

// ===== Loop demo =====
void loop() {
  setServoAngle(0);
  delay(1000);

  setServoAngle(90);
  delay(1000);

  setServoAngle(180);
  delay(1000);

  setServoAngle(90);
  delay(1000);
}