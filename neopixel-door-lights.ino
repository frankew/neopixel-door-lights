#include <Adafruit_NeoPixel.h>
#include <Button.h>
#include "Adafruit_NeoPatterns.h"
#include "NeoPixel_Animator.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

const byte leftDoorLEDStripPin = 8;   // connected to NeoPixels.
const byte leftDoorSwitchPin = 12;    // connected to left door switch.
Button leftDoorButton(leftDoorSwitchPin, true, true, 50);
NeoPatterns leftDoorLEDs = NeoPatterns(30, leftDoorLEDStripPin, NEO_RGB + NEO_KHZ800, &leftDoorLEDsComplete);

const byte rightDoorLEDStripPin = 9;   // connected to NeoPixels.
const byte rightDoorSwitchPin = 11;    // connected to right door switch.
Button rightDoorButton(rightDoorSwitchPin, true, true, 50);
NeoPatterns rightDoorLEDs = NeoPatterns(30, rightDoorLEDStripPin, NEO_RGB + NEO_KHZ800, &rightDoorLEDsComplete);

uint32_t offColor = rightDoorLEDs.Color(0,0,0);
uint32_t onColor = rightDoorLEDs.Color(255, 248, 248);

void setup() {
  Serial.begin(9600);
  pinMode(leftDoorLEDStripPin, OUTPUT);
  pinMode(rightDoorLEDStripPin, OUTPUT);
  leftDoorLEDs.begin();
  leftDoorLEDs.ColorSet(offColor);
  leftDoorLEDs.show();
  rightDoorLEDs.begin();
  rightDoorLEDs.ColorSet(offColor);
  rightDoorLEDs.show();
}

void loop() {

    leftDoorButton.read();
    if (leftDoorButton.wasReleased()) {   // Door has opened, turn up light
      leftDoorLEDs.Fade(leftDoorLEDs.getPixelColor(0), onColor, 10, 25, FORWARD);
    }
    if (leftDoorButton.wasPressed()) {   // Door has closed, turn off light
      leftDoorLEDs.Fade(leftDoorLEDs.getPixelColor(0), offColor, 10, 15, FORWARD);
    }
    leftDoorLEDs.Update();

    rightDoorButton.read();
    if (rightDoorButton.wasReleased()) {   // Door has opened, turn up light
      rightDoorLEDs.Fade(rightDoorLEDs.getPixelColor(0), onColor, 10, 25, FORWARD);
    }
    if (rightDoorButton.wasPressed()) {   // Door has closed, turn off light
      rightDoorLEDs.Fade(rightDoorLEDs.getPixelColor(0), offColor, 10, 15, FORWARD);
    }
    rightDoorLEDs.Update();
}

void leftDoorLEDsComplete() {
  leftDoorLEDs.ActivePattern = NONE;
  leftDoorButton.read();
  if (leftDoorButton.isPressed()) {
    leftDoorLEDs.ColorSet(offColor);
  }
}

void rightDoorLEDsComplete() {
  rightDoorLEDs.ActivePattern = NONE;
  rightDoorButton.read();
  if (rightDoorButton.isPressed()) {
    rightDoorLEDs.ColorSet(offColor);
  }
}
