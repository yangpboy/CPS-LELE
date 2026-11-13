
#include <AccelStepper.h>
#include <Servo.h>

// ===== 1. 四个步进电机 =====
AccelStepper leftArm(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper rightArm(AccelStepper::HALF4WIRE, 6, 8, 7, 9);
AccelStepper leftLeg(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper rightLeg(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

// ===== 2. 四个 Servo =====
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// 最大行程：20圈
const long MAX_STEPS = 4096L * 20;

char buffer[64];
int index = 0;

// Servo 运动参数
int servoStart[4] = {30, 30, 30, 30};
int servoAngle = 0;
int servoDirection = 1;
int servoInterval = 15;
unsigned long lastServoUpdate = 0;

// ===== 3. 初始化 =====
void setup() {
  Serial.begin(9600);

  AccelStepper* motors[] = {
    &leftArm, &rightArm, &leftLeg, &rightLeg
  };

  for (int i = 0; i < 4; i++) {
    motors[i]->setMaxSpeed(1300);
    motors[i]->setAcceleration(250);
    motors[i]->setCurrentPosition(0);
  }

  // 四个 Servo
  servo1.attach(22);
  servo2.attach(23);
  servo3.attach(24);
  servo4.attach(25);

servo1.write(servoStart[0]);
servo2.write(servoStart[1]);
servo3.write(servoStart[2]);
servo4.write(servoStart[3]);
}

// ===== 4. 接收 Wekinator 5 个输出 =====
void readData(char* data) {
  float values[5];

  char* token = strtok(data, ",");

  for (int i = 0; i < 5; i++) {
    if (token == NULL) return;
    values[i] = atof(token);
    token = strtok(NULL, ",");
  }

  // Regression 1–4：控制四个 Stepper
  leftArm.moveTo(constrain(values[0], 0.0, 1.0) * MAX_STEPS);
  rightArm.moveTo(constrain(values[1], 0.0, 1.0) * MAX_STEPS);
  leftLeg.moveTo(constrain(values[2], 0.0, 1.0) * MAX_STEPS);
  rightLeg.moveTo(constrain(values[3], 0.0, 1.0) * MAX_STEPS);

  // Classification 5：控制四个 Servo 速度
  int classValue = round(values[4]);

  if (classValue == 1) {
    servoInterval = 15;
  }
  else if (classValue == 2) {
    servoInterval = 5;
  }
}

// ===== 5. 四个 Servo 同步往复 =====
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

servo1.write(constrain(servoStart[0] + servoAngle, 0, 180));
servo2.write(constrain(servoStart[1] + servoAngle, 0, 180));
servo3.write(constrain(servoStart[2] + servoAngle, 0, 180));
servo4.write(constrain(servoStart[3] + servoAngle, 0, 180));
  }
}

// ===== 6. 主循环 =====
void loop() {

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      buffer[index] = '\0';
      readData(buffer);
      index = 0;
    }
    else if (c != '\r') {
      if (index < 63) {
        buffer[index++] = c;
      }
      else {
        index = 0;
      }
    }
  }

  // 四个 Stepper 独立运行
  leftArm.run();
  rightArm.run();
  leftLeg.run();
  rightLeg.run();

  // 四个 Servo 同步往复
  updateServos();
}
