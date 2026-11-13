#include <Stepper.h>

// 每圈步数（28BYJ-48 常用值）
const int stepsPerRevolution = 2048;

// 引脚连接：IN1=D6, IN2=D7, IN3=D8, IN4=D9
Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9);

void setup() {
  // 设置旋转速度 RPM
  myStepper.setSpeed(10);

  Serial.begin(9600);
}

void loop() {
  // 持续顺时针旋转
  myStepper.step(stepsPerRevolution);
}