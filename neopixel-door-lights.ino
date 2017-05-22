#include <Adafruit_NeoPixel.h>
#include <Button.h>
#include "Adafruit_NeoPatterns.h"
#include "NeoPixel_Animator.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

const byte leftLEDStripPin = 4;   // connected to left LED strip.
const byte leftSwitchPin = 6;    // connected to left door switch.
Button leftButton(leftSwitchPin, true, true, 50);
NeoPatterns leftLEDs = NeoPatterns(30, leftLEDStripPin, NEO_RGB + NEO_KHZ800, &leftLEDsComplete);

const byte rightLEDStripPin = 8; //10;   // connected to right LED strip.
const byte rightSwitchPin = 12;    // connected to right door switch.
Button rightButton(rightSwitchPin, true, true, 50);
NeoPatterns rightLEDs = NeoPatterns(30, rightLEDStripPin, NEO_RGB + NEO_KHZ800, &rightLEDsComplete);

uint32_t offColor = rightLEDs.Color(0,0,0);
uint32_t onColor = rightLEDs.Color(255, 248, 248);

void setup() {
  Serial.begin(9600);
  pinMode(leftLEDStripPin, OUTPUT);
  pinMode(rightLEDStripPin, OUTPUT);
  leftLEDs.begin();
  leftLEDs.ColorSet(offColor);
  leftLEDs.show();
  rightLEDs.begin();
  rightLEDs.ColorSet(offColor);
  rightLEDs.show();
}

void loop() {

    leftButton.read();
    if (leftButton.wasReleased()) {   // door has opened, turn up light
      leftLEDs.Fade(leftLEDs.getPixelColor(0), onColor, 10, 25, FORWARD);
    }
    if (leftButton.wasPressed()) {   // door has closed, turn off light
      leftLEDs.Fade(leftLEDs.getPixelColor(0), offColor, 10, 15, FORWARD);
    }
    leftLEDs.Update();

    rightButton.read();
    if (rightButton.wasReleased()) {   // door has opened, turn up light
      rightLEDs.Fade(rightLEDs.getPixelColor(0), onColor, 10, 25, FORWARD);
    }
    if (rightButton.wasPressed()) {   // door has closed, turn off light
      rightLEDs.Fade(rightLEDs.getPixelColor(0), offColor, 10, 15, FORWARD);
    }
    rightLEDs.Update();
}

void leftLEDsComplete() {
  leftLEDs.ActivePattern = NONE;
  leftButton.read();
  if (leftButton.isPressed()) {
    leftLEDs.ColorSet(offColor);
  }
}

void rightLEDsComplete() {
  rightLEDs.ActivePattern = NONE;
  rightButton.read();
  if (rightButton.isPressed()) {
    rightLEDs.ColorSet(offColor);
  }
}
