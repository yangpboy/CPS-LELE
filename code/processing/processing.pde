
/*
  Based on Becky Stewart's processing_osc_to_arduino (2022)

  Wekinator -> Processing -> Arduino
  5 Outputs -> 4 Steppers + Servos
*/

import oscP5.*;
import netP5.*;
import processing.serial.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

Serial port;

// Store 5 Wekinator outputs
float[] outputs = new float[5];

// Send interval: 300ms
int lastSendTime = 0;
int sendInterval = 300;
boolean receivedData = false;

void setup() {
  size(256, 150);

  println("Available serial ports:");
  printArray(Serial.list());

  // Arduino serial port
  port = new Serial(this, "/dev/cu.usbmodem21201", 9600);

  // Receive OSC from Wekinator
  oscP5 = new OscP5(this, 12000);
}

void draw() {

  // Background
  for (int i = 0; i < 256; i++) {
    stroke(i);
    line(i, 0, i, 150);
  }

  // Send every 300ms
  if (receivedData && millis() - lastSendTime >= sendInterval) {
    updateArduino();
    lastSendTime = millis();
  }
}

void oscEvent(OscMessage theOscMessage) {

  if (theOscMessage.checkAddrPattern("/wek/outputs") == true) {

    // Receive 5 floats
    if (theOscMessage.checkTypetag("fffff")) {

      for (int i = 0; i < 5; i++) {
        outputs[i] = theOscMessage.get(i).floatValue();
      }

      receivedData = true;
      return;
    }
  }
}

// Send 5 outputs to Arduino
void updateArduino() {

  // Limit first 4 outputs to 0-1
  String arduinoMessage =
    constrain(outputs[0], 0, 1) + "," +
    constrain(outputs[1], 0, 1) + "," +
    constrain(outputs[2], 0, 1) + "," +
    constrain(outputs[3], 0, 1) + "," +
    round(outputs[4]) + "\n";

  // Send to Arduino
  port.write(arduinoMessage);

  // Print debug data
  println("Sent: " + arduinoMessage.trim());
}
