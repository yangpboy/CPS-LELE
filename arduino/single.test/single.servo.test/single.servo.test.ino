#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {
  // 90° → 180°
  for (int angle = 90; angle <= 120; angle++) {
    myServo.write(angle);
    delay(30);
  }

  // 180° → 90°
  for (int angle = 120; angle >= 90; angle--) {
    myServo.write(angle);
    delay(30);
  }
}