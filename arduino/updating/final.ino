#include <AccelStepper.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义4个步进电机 / Define 4 stepper motors
AccelStepper head(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper leftarm(AccelStepper::HALF4WIRE, 6, 8, 7, 9);
AccelStepper rightarm(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper leftleg(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

// 每圈约4096步 / Approx. 4096 steps per turn
// 限制36圈 / Limit to 36 turn for testing
const long MAX_STEPS = 4096L * 36;

//把陆续收到的字符暂存起来
char receiveBuffer[64];
byte receiveLength = 0;
bool discardLine = false;

void setup() {
  Serial.begin(9600);

  // 设置电机速度 / Set motor speed
  head.setMaxSpeed(1300);
  leftarm.setMaxSpeed(1300);
  rightarm.setMaxSpeed(1300);
  leftleg.setMaxSpeed(1300);

  // 设置加速度 / Set acceleration
  head.setAcceleration(250);
  leftarm.setAcceleration(250);
  rightarm.setAcceleration(250);
  leftleg.setAcceleration(250);

  // 将当前位置设为0 / Set current position to zero
  head.setCurrentPosition(0);
  leftarm.setCurrentPosition(0);
  rightarm.setCurrentPosition(0);
  leftleg.setCurrentPosition(0);
}

// 四个电机是否全部到达目标
bool allArrived() {
  return head.distanceToGo() == 0 &&
         leftarm.distanceToGo() == 0 &&
         rightarm.distanceToGo() == 0 &&
         leftleg.distanceToGo() == 0;
}

// 解析完整消息，并设置四个目标位置
void applyMessage(char *data) {
  float values[4];
  char *part = data;

  for (int i = 0; i < 4; i++) {
    char *comma = strchr(part, ',');

    // 必须正好是四个数、三个逗号
    if (i < 3 && comma == NULL) return;
    if (i == 3 && comma != NULL) return;

    if (comma != NULL) {
      *comma = '\0';
    }

    // 检查是否为有效数字
    char *end;
    double value = strtod(part, &end);

    if (end == part) return;

    // 允许数字后有空格
    while (*end == ' ' || *end == '\t') {
      end++;
    }

    if (*end != '\0' || isnan(value) || isinf(value)) {
      return;
    }

    values[i] = constrain((float)value, 0.0f, 1.0f);

    if (comma != NULL) {
      part = comma + 1;
    }
  }

  head.moveTo((long)(values[0] * MAX_STEPS));
  leftarm.moveTo((long)(values[1] * MAX_STEPS));
  rightarm.moveTo((long)(values[2] * MAX_STEPS));
  leftleg.moveTo((long)(values[3] * MAX_STEPS));
}

void loop() {

if (Serial.available() > 0) {
  char c = Serial.read();
  //每次只读取一个字符

// 运动期间收到的整条消息都丢弃
    if (!allArrived()) {
      discardLine = true;
    }

    if (c == '\n') {
      // 只有消息完整、没有被丢弃、四个电机全部到位，
      // 才执行这条消息
      if (!discardLine &&
          receiveLength > 0 &&
          allArrived()) {
        receiveBuffer[receiveLength] = '\0';
        applyMessage(receiveBuffer);
      }

      // 为下一条消息重新准备
      receiveLength = 0;
      discardLine = false;

    } else if (c != '\r') {
      if (!discardLine) {
        if (receiveLength < sizeof(receiveBuffer) - 1) {
          receiveBuffer[receiveLength++] = c;
        } else {
          // 消息过长，整条丢弃
          discardLine = true;
        }
      }
    }
  }

  // 无论有没有收到消息，都持续驱动四个电机
  head.run();
  leftarm.run();
  rightarm.run();
  leftleg.run();
}