
#include <AccelStepper.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ===== 1. Set up four stepper motors =====
AccelStepper head(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper leftarm(AccelStepper::HALF4WIRE, 6, 8, 7, 9);
AccelStepper rightarm(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper leftleg(AccelStepper::HALF4WIRE, A0, A2, A1, A3);

// About 4096 steps per turn
// Limit movement to 6 turns for testing
const long MAX_STEPS = 4096L * 6;

// Store incoming characters until a full message is received
char receiveBuffer[64];
byte receiveLength = 0;
bool discardLine = false;

void setup() {
  Serial.begin(9600);

  // Set the maximum speed of each motor
  head.setMaxSpeed(1300);
  leftarm.setMaxSpeed(1300);
  rightarm.setMaxSpeed(1300);
  leftleg.setMaxSpeed(1300);

  // Set the acceleration of each motor
  head.setAcceleration(250);
  leftarm.setAcceleration(250);
  rightarm.setAcceleration(250);
  leftleg.setAcceleration(250);

  // Set the current position of each motor to zero
  head.setCurrentPosition(0);
  leftarm.setCurrentPosition(0);
  rightarm.setCurrentPosition(0);
  leftleg.setCurrentPosition(0);
}

// Check if all four motors have reached their target positions
bool allArrived() {
  return head.distanceToGo() == 0 &&
         leftarm.distanceToGo() == 0 &&
         rightarm.distanceToGo() == 0 &&
         leftleg.distanceToGo() == 0;
}

// Read a full message and set four target positions
void applyMessage(char *data) {
  float values[4];
  char *part = data;

  for (int i = 0; i < 4; i++) {
    char *comma = strchr(part, ',');

    // The message must have exactly 4 numbers and 3 commas
    if (i < 3 && comma == NULL) return;
    if (i == 3 && comma != NULL) return;

    if (comma != NULL) {
      *comma = '\0';
    }

    // Check if the value is a valid number
    char *end;
    double value = strtod(part, &end);

    if (end == part) return;

    // Allow spaces after the number
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

  // Read one character at a time

  // Ignore the full message if motors are still moving
    if (!allArrived()) {
      discardLine = true;
    }

    if (c == '\n') {
      // Only use the message if it is complete,
      // has not been ignored, and all motors have stopped
      if (!discardLine &&
          receiveLength > 0 &&
          allArrived()) {
        receiveBuffer[receiveLength] = '\0';
        applyMessage(receiveBuffer);
      }

      // Reset for the next message
      receiveLength = 0;
      discardLine = false;

    } else if (c != '\r') {
      if (!discardLine) {
        if (receiveLength < sizeof(receiveBuffer) - 1) {
          receiveBuffer[receiveLength++] = c;
        } else {
          // Ignore the full message if it is too long
          discardLine = true;
        }
      }
    }
  }

  // Keep all four motors running, even without new messages
  head.run();
  leftarm.run();
  rightarm.run();
  leftleg.run();
}
