#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment(); // declare LED object

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
}

void loop() {

// Countdown
  for(int i = 0; i < 11; i++){
    matrix.println(i);
    matrix.writeDisplay();
    delay(1000);
    }

delay(5000);

// Print a 4 digit float.
    float i = 7777;
    matrix.println(i);
    matrix.writeDisplay();

delay(5000);

// Make colon dot light up.
for(int i = 0; i < 5; i++){
      matrix.writeDigitNum(i,1, true);
      matrix.writeDisplay();
      delay(1000);
      }
delay(5000);
}
