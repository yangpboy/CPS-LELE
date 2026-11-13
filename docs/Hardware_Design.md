# Hardware Design

## 1. Hardware Overview

Lele uses an Arduino Mega 2560 to control four 28BYJ-48 stepper motors and four SG90 servo motors. The stepper motors adjust the pitch of the four strings, while the servos control the individual strumming picks.

## 2. Components & Selection

| Component | Quantity | Function |
|---|---:|---|
| Arduino Mega 2560 | 1 | Main controller |
| 28BYJ-48 Stepper Motor | 4 | String pitch adjustment |
| Stepper Motor Driver | 4 | Stepper motor control |
| SG90 Servo Motor | 4 | Strumming pick control |
| Power Board | 1 | Power distribution |
| External 5V Supply | 1 | Motor power |
| Jumper Wires & USB Cable | Multiple | Electrical connections |

**Arduino Mega:** We initially used an Arduino Nano but switched to a Mega for its additional I/O pins, allowing all motors to be connected directly without an expansion board.

**Stepper Motors:** Chosen for their ability to control rotational positions through step counts, enabling independent pitch adjustment for each string.

**Servo Motors:** We used four individual SG90 servos instead of a more complicated pick-switching mechanism, simplifying the mechanical design.

## 3. Circuit Design

<img width="1416" height="984" alt="Group 14 (1)" src="https://github.com/user-attachments/assets/7ee26dca-5e92-49eb-b4c6-82db76e1c289" />

### Pin Mapping

| Motor | Arduino Mega Pins |
|---|---|
| Left Arm Stepper | D2–D5 |
| Right Arm Stepper | D6–D9 |
| Left Leg Stepper | D10–D13 |
| Right Leg Stepper | A0–A3 |
| SG90 Servos (×4) | See final Arduino sketch |

Each stepper motor connects through its own driver board. The servos receive control signals from the Arduino and power from the external 5V supply.

## 4. Power Supply & Consumption

The motors are powered by an external 5V supply through the power board, while the Arduino connects to the laptop via USB. Both share a common ground.

The power board is labelled with 0.6A and 2A current limits. During development, we added a bridge connection between the labelled points, intending to increase the available current. The exact effect of this connection has not been verified.

### Estimated Motor Current

| Component | Quantity | Estimated Total |
|---|---:|---:|
| 28BYJ-48 Steppers | 4 | 400–1000 mA |
| SG90 Servos | 4 | 400–1000 mA |
| **Total** | **8** | **800–2000 mA** |

These are approximate operating-current estimates, not measured values. Actual consumption depends on motor load and movement, and peak current may be higher.

During testing, simultaneous motor operation presented power-related challenges. Future improvements could include measuring the actual current demand, verifying the power board configuration and securing the wiring more permanently.
