#include <DIO2.h>
#include <Adafruit_NeoPixel.h>
#define LED_PIN    8
#define LED_COUNT 60
long int RED = 0xFF0000;
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
  RED,
  RED,
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
long lastTimeStateChanged[] = {
  0, 0, 0, 0, 0, 0
};
boolean buttonState[6];
//this was originally included for adding a debounce timer
//but since I started using capacitors properly I don't need this
//long smallestTimeBetweenEvents = 20;
char str[4];
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  for (byte i = 0; i < 6; i++) {
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT);
    pinMode(inputPins[i], INPUT_PULLUP);
  }
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
    if (*s == HIGH) {
      //high read for button

      if (lastValue != *s/* && now - lastTimeStateChanged[i] > smallestTimeBetweenEvents*/) {
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
        lastTimeStateChanged[i] = now;
      }
    } else {
      //low read for button
      if (lastValue != *s/* && now - lastTimeStateChanged[i] > smallestTimeBetweenEvents*/) {
        //buttonState[i] = !buttonState[i];
        Serial.print("button was released");
        Serial.print(i);
        Serial.println("");
        Serial1.write(i + 6);
        analogWrite(outputPins[i], 0);
        lastTimeStateChanged[i] = now;
      }
    }
    s++;
  }
  //we need to go through button state to find out what was the last pressed one
  int minimum, current, minI;
  for (int i = 0; i < 6; i++) {
    current = lastTimeStateChanged[i];
    if (current < minimum) {
      minimum = current;
      minI = i;
    }
  }
  //make sure something is pressed at least
  bool isSomethingPressed = false;
  for (int i = 0; i < 6; i++) {
    if (buttonState[i] == HIGH) {
      isSomethingPressed = true;
    }
  }
  if (isSomethingPressed == false) {
    strip.clear();
    strip.show();
  }
}
