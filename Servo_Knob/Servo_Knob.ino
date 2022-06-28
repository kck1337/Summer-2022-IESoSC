#include <Servo.h>    // Include servo library

Servo myservo;        // Create servo object "myservo"

int potPin = A0;      // Define pin for the potentiometer  
int val = 0;          // Initialzie variable


void setup() {
  myservo.attach(9);  // Assign a pin number to the servo object  
  
}

void loop() {
  val = analogRead(potPin);        // store potetiometer reading to variable val 
  val = map(val, 0, 1023, 0, 180); // map val from 0-1023 to 0-180 degrees 
  myservo.write(val);              // Set the servo angle based on pot knob
  delay(15);                       // Pause for 15 ms
}
