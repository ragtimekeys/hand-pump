#include <DIO2.h>
#include <Adafruit_NeoPixel.h>
#define LED_PIN    8
#define LED_COUNT 60
long int REDD = 0xFF0000;
long int YELLOW = 0xFFFF00;
long int BLUE = 0x0000FF;
long int WHITE = 0xFFFFFF;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int outputPins[] = {
  //BlueLeft
  3,
  //BlueRight
  2,
  //RedRight
  6,
  //RedLeft
  5,
  //Yellow
  4,
  //White
  7
};
long int padColors[] = {
  BLUE,
  BLUE,
  REDD,
  REDD,
  YELLOW,
  WHITE
};
int inputPins[] = {
  53,
  49,
  45,
  41,
  37,
  33
};
long lastTimeSentSomething[] = {
  0, 0, 0, 0, 0, 0
};
boolean buttonState[6];
long smallestTimeBetweenEvents = 20;
char str[4];
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  for (byte i = 0; i < 6; i++) {
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT);
    pinMode(inputPins[i], INPUT_PULLUP);
  }
//  Keyboard.begin();
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}
void loop() {
  boolean *s = buttonState;
  long now = millis();
  for (byte i = 0; i < 6; i++) {
    boolean lastValue = *s;
    *s = !digitalRead2(inputPins[i]);
    if (*s == HIGH) {csezqeszezcqcqszezcscseece
      //high read for button
      /*
      */
      if (lastValue != *s && now - lastTimeSentSomething[i] > smallestTimeBetweenEvents) {
        //buttonState[i] = !buttonState[i];
        Serial.print("button was pressed");
        Serial.print(i);
        Serial.println("");
        Serial1.write(i);
        for (int j = 0; j < LED_COUNT; j++) {
          strip.setPixelColor(j, padColors[i]);
        }
        strip.show();
        analogWrite(outputPins[i], 127);
        lastTimeSentSomething[i] = now;
      }
    } else {
      //low read for button
      if (lastValue != *s && now - lastTimeSentSomething[i] > smallestTimeBetweenEvents) {
        //buttonState[i] = !buttonState[i];
        Serial.print("button was released");
        Serial.print(i);
        Serial.println("");
        Serial1.write(i + 6);
        analogWrite(outputPins[i], 0);
        lastTimeSentSomething[i] = now;
      }
    }
    s++;
  }
  //we need to go through button state to find out what was the last pressed one
  int minimum, current, minI;
  for (int i = 0; i < 6; i++) {
    current = lastTimeSentSomething[i];
    if (current < minimum) {
      minimum = current;
      minI = i;
    }
  }
  //make sure something is pressed at least
  bool isSomethingPressed = false;
  for (int i = 0; i<6; i++) {
    if (buttonState[i] == HIGH) {
      isSomethingPressed = true;
    }
  }
  if (isSomethingPressed == false) {
    strip.clear();
    strip.show();
  }
}
