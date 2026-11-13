
#include <AccelStepper.h>
#include <Servo.h>

// ===== 1. Set up four stepper motors (same pins) =====
AccelStepper leftArm(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper rightArm(AccelStepper::HALF4WIRE, 6, 8, 7, 9);
AccelStepper leftLeg(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper rightLeg(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

// ===== 2. Set up four servo motors =====
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Set servo movement values
int servoAngle = 40;
int servoDirection = 1;
const int servoInterval = 15;
unsigned long lastServoUpdate = 0;

void setup() {
  Serial.begin(9600);

  // ===== Set up stepper motors =====
  leftArm.setMaxSpeed(1000);
  rightArm.setMaxSpeed(1000);
  leftLeg.setMaxSpeed(1000);
  rightLeg.setMaxSpeed(1000);

  // Set continuous rotation speed (steps/s)
  leftArm.setSpeed(-1000);
  rightArm.setSpeed(-1000);
  leftLeg.setSpeed(-1000);
  rightLeg.setSpeed-(1000);

  // ===== Set up servo motors =====
  servo1.attach(22);
  servo2.attach(23);
  servo3.attach(24);
  servo4.attach(25);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

// ===== 3. Move servos back and forth =====
void updateServos() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastServoUpdate >= servoInterval) {
    lastServoUpdate = currentMillis;

    servoAngle += servoDirection;

    if (servoAngle >= 90) {
      servoAngle = 90;
      servoDirection = -1;
    }
    else if (servoAngle <= 0) {
      servoAngle = 0;
      servoDirection = 1;
    }

    servo1.write(servoAngle);
    servo2.write(servoAngle);
    servo3.write(servoAngle);
    servo4.write(servoAngle);
  }
}

// ===== 4. Main loop =====
void loop() {

  // Keep all four stepper motors turning
  leftArm.runSpeed();
  rightArm.runSpeed();
  leftLeg.runSpeed();
  rightLeg.runSpeed();

  // Move all four servos back and forth together
  updateServos();
}
