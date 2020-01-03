/*
  How to change name of arduino device:
  https://github.com/MHeironimus/ArduinoJoystickLibrary/issues/14#issuecomment-263529830

  using this library
  https://github.com/MHeironimus/ArduinoJoystickLibrary
*/

#include <Joystick.h>


Joystick_ Joystick;

// for incoming serial data
int incomingByte = 0;
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial && millis() < 2000) {};
  Joystick.begin();
  Serial.println("Leonardo ready");
}
void loop() {
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    //key presses are sent from the MEGA as numbers less than 6
    if (incomingByte < 6) {
      Joystick.setButton(incomingByte, HIGH);
    }
    //and >=6 for releases
    else {
      Joystick.setButton(incomingByte - 6, LOW);
    }
    Serial.print("Received from MEGA: ");
    Serial.println(incomingByte, DEC);
  }
}
