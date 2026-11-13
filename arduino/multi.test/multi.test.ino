
#include <AccelStepper.h>
#include <Servo.h>

// ===== 1. 四个 Stepper（原引脚不变）=====
AccelStepper leftArm(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper rightArm(AccelStepper::HALF4WIRE, 6, 8, 7, 9);
AccelStepper leftLeg(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper rightLeg(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

// ===== 2. 四个 Servo =====
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Servo 运动参数
int servoAngle = 40;
int servoDirection = 1;
const int servoInterval = 15;
unsigned long lastServoUpdate = 0;

void setup() {
  Serial.begin(9600);

  // ===== Stepper 初始化 =====
  leftArm.setMaxSpeed(1000);
  rightArm.setMaxSpeed(1000);
  leftLeg.setMaxSpeed(1000);
  rightLeg.setMaxSpeed(1000);

  // 持续旋转速度（steps/s）
  leftArm.setSpeed(-1000);
  rightArm.setSpeed(-1000);
  leftLeg.setSpeed(-1000);
  rightLeg.setSpeed-(1000);

  // ===== Servo 初始化 =====
  servo1.attach(22);
  servo2.attach(23);
  servo3.attach(24);
  servo4.attach(25);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

// ===== 3. Servo 往复运动 =====
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

// ===== 4. 主循环 =====
void loop() {

  // 四个 Stepper 同时持续旋转
  leftArm.runSpeed();
  rightArm.runSpeed();
  leftLeg.runSpeed();
  rightLeg.runSpeed();

  // 四个 Servo 同时往复旋转
  updateServos();
}
