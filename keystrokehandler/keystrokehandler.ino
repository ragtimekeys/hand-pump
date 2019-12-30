#include <Keyboard.h>

int incomingByte = 0; // for incoming serial data
//String letters = "zceqsx";
int letters[] = {122, 99, 113, 101, 115, 120};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial && millis()<2000)
  {
    // do nothing
  } ;
  Keyboard.begin();
  Serial.println("Leonardo ready");
}
void loop() {
  // put your main code here, to run repeatedly
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    //Keyboard.press("a");
    //Keyboard.release("a");
    // say what you got:
    if (incomingByte < 6) {
      //this means it was a key press
      Keyboard.press(letters[incomingByte]);
    } else {
      Keyboard.release(letters[incomingByte-6]);
    }
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
