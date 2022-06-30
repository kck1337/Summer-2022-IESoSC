#include <Wire.h>
#include <Digital_Light_ISL29035.h>
#include <Digital_Light_TSL2561.h>

int knockSensor = A0;
byte val = 0;
int Threshold = 7;
int counter;
int prevSensor = 1023;
int statePin = LOW;
int prev_val = 3;
int newcounter;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  TSL2561.init();
}

void loop() {
  Serial.println("-----Laser as counter-----");
  int sensor = TSL2561.readVisibleLux();
  Serial.print("The light value is: ");
  Serial.println(TSL2561.readVisibleLux());

  if(sensor<1000 and prevSensor>1000){
    counter = counter+1;
    Serial.print("Count of people is: ");
    Serial.println(counter);
  }
  else{
    Serial.println(counter);
  }
  prevSensor = sensor;

  Serial.println("-----Piezo as counter-----");

  val = analogRead(knockSensor);
  Serial.print("Piezo sensor value is: ");
  Serial.println(val);

  if(val >= Threshold and prev_val <= Threshold){
    newcounter = newcounter + 1;
    Serial.println("Knock!");
    Serial.println(newcounter);
    delay(100);
  }
  prev_val = val;
  delay(100);
}
