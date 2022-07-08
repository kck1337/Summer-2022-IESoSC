#include <Servo.h>    // Include servo library

Servo myservo;        // Create servo object "myservo"
int potPin = A0;      // Define pin for the potentiometer  
int val = 0;          // Initialzie variable

void setup() {  
  myservo.attach(9);  // Assign a pin number to the servo object  
}
void loop() {
  for(int pos = 0; pos <= 180; pos++){       // Sweep servo from 0 to 180 degrees
    myservo.write(pos);                      // write servo position 
    delay(15);                               // Pause 15 ms
    }
  for(int pos = 180; pos >= 0; pos--){
    myservo.write(pos);
    delay(15);
    }
}
