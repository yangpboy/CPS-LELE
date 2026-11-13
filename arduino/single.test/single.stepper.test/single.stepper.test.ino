
#include <Stepper.h>

// Number of steps per turn (28BYJ-48)
const int stepsPerRevolution = 2048;

// Pin connections: IN1=D6, IN2=D7, IN3=D8, IN4=D9
Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9);

void setup() {
  // Set the motor speed in RPM
  myStepper.setSpeed(10);

  Serial.begin(9600);
}

void loop() {
  // Keep the motor turning clockwise
  myStepper.step(stepsPerRevolution);
}
