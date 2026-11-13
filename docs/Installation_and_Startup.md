
# Installation & Startup Guide

This guide explains how to set up and run Lele, an interactive system that translates body movements into physical mechanical responses inspired by the four strings of a ukulele.

## 1.1 Requirements

### Hardware

- Arduino Mega 2560
- 4 × 28BYJ-48 5V stepper motors
- 4 × stepper motor driver boards
- 4 × servo motors
- External 5V power supply with sufficient current capacity
- 1 × power board
- USB cable, jumper wires
- Lele mechanical structure

### Software

- Python 3 with compatible dependencies (MediaPipe, OpenCV, NumPy and python-osc)
- Wekinator with body training data
- Processing with oscP5 and Serial libraries
- Arduino IDE with AccelStepper and Servo libraries

## 1.2 Install Dependencies

Install the required Python libraries in a compatible Python environment:

```bash
python -m pip install opencv-python mediapipe numpy python-osc
```

Install the following additional software:

- Arduino IDE
- Processing
- Wekinator

In the Arduino IDE, install the AccelStepper library through Library Manager. The Servo library is included with standard Arduino IDE installations.

In Processing, install the oscP5 library through the Contribution Manager.

**Note:** Use a tested Python environment and record the exact dependency versions. MediaPipe API compatibility can vary between releases.

## 1.3 Hardware Setup

1. Connect the four stepper motors to their driver boards.
2. Connect the driver inputs to the Arduino Mega according to the pin mapping below.
3. Connect the four servo signal wires to the pins specified in the final Arduino sketch.
4. Connect the external 5V supply to the motor power distribution system.
5. Connect the Arduino Mega to the computer via USB.
6. Ensure that the Arduino and external motor power supply share a common ground.

| Stepper Motor | Arduino Mega Pins |
|---|---|
| Left arm | D2, D3, D4, D5 |
| Right arm | D6, D7, D8, D9 |
| Left leg | D10, D11, D12, D13 |
| Right leg | A0, A1, A2, A3 |

**Safety:** Check the motor supply voltage and current capacity before powering the system. Do not power all motors directly from the Arduino's 5V pin.

## 1.4 Upload Arduino Code

1. Open the final Arduino `.ino` file in Arduino IDE.
2. Select Arduino Mega or Mega 2560 as the board.
3. Select the correct USB serial port.
4. Upload the sketch.
5. Check that the Arduino initialises correctly.
6. Close the Serial Monitor before running Processing.

The communication baud rate is **9600**.

The Arduino sketch receives motor-control values through the serial connection and updates the physical actuators.

## 1.5 Configure Wekinator

Open Wekinator and load the trained Lele project.

Verify the OSC configuration:

| Setting | Value |
|---|---|
| Input port | 6448 |
| Input OSC message | `/wek/inputs` |
| Output destination | `127.0.0.1` |
| Output port | 12000 |
| Output OSC message | `/wek/outputs` |

The final Python script sends **23 input features** to Wekinator, including 22 body-relative coordinates from 11 landmarks and one hip-sway feature.

Wekinator produces five outputs: four regression values for the stepper motors and one classification output for the servo motors.

The regression outputs represent the movement of the four limbs. The classifier controls a second category of mechanical behaviour.

Load the saved training data and models, then start Wekinator's model execution.

## 1.6 Start Processing

1. Open the final Processing `.pde` file.
2. Check the serial port using `Serial.list()`.
3. Update the port name if the Arduino is connected to a different USB port.
4. Confirm the serial baud rate is **9600**.
5. Run the Processing sketch.

Processing receives OSC messages from Wekinator on port **12000** and sends the resulting motor-control data to Arduino approximately every **300 ms**.

The serial port must not be occupied by another application.

## 1.7 Start Python Pose Tracking

Ensure the MediaPipe model file `pose_landmarker.task` is available in the expected location.

Run the final Python script:

```bash
python body.py
```

The default camera ID is `0`. If the camera cannot be opened, check the camera permissions and select the correct camera ID.

When running successfully:

- The webcam captures the participant's movements.
- MediaPipe detects body landmarks.
- Body-relative coordinates are calculated.
- The input values are transmitted to Wekinator via OSC.

Press **Esc** or use the stop button to close the pose-tracking window.

## 1.8 Recommended Startup Sequence

1. Connect and check the hardware.
2. Upload the Arduino sketch.
3. Start the motor power supply.
4. Open Wekinator and load the trained project.
5. Run Processing and establish serial communication.
6. Start the Wekinator model.
7. Run Python pose tracking.
8. Stand in front of the webcam and test each limb movement individually.
9. Perform combined movements to test the complete system.

## 1.9 Expected Behaviour

When the system is functioning correctly, changes in body posture should produce corresponding mechanical movement.

- Left arm movement controls the first stepper motor.
- Right arm movement controls the second stepper motor.
- Left leg movement controls the third stepper motor.
- Right leg movement controls the fourth stepper motor.
- Hip-related movement changes the servo-driven response.

If the physical output does not respond, check each communication stage separately using the system's [Testing and Debugging](docs/Testing%20and%20Debugging.md)guide.
