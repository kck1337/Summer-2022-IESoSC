#include <Servo.h>

// Create servo object
Servo myservo;

// Variable to store servo position
int pos = 0;

// Variable to store volatge value
float x=0;

float ledVal, Voltage;
int leftSensor, rightSensor; 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  leftSensor = analogRead(A0);
  rightSensor = analogRead(A1);
  ledVal = analogRead(A2);
  Voltage = ledVal * (5.0/1023.0);

  Serial.print("Voltage = ");
  Serial.println(Voltage);
  Serial.print("Right Sensor = ");
  Serial.println(rightSensor);
  Serial.print("Left Sensor = ");
  Serial.println(leftSensor);

  pos = myservo.read();
  if (rightSensor > 250 || leftSensor > 250){
    if(abs(rightSensor-leftSensor)<= 150){
      goto next;
      }
    // Move servo right if right sensor is high

    // Move servo left if left sensor is high

    }
    next:
    delay(100);
}
