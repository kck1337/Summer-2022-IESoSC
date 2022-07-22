#include <Wire.h>
#include <Digital_Light_TSL2561.h>
int people = 0;
int fsr_pin = A0;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  TSL2561.init();
  pinMode(fsr_pin, INPUT);
}

void loop()
{
  int lux = TSL2561.readVisibleLux();
  int weight = analogRead(fsr_pin);
  if(lux < 1000 and weight > 500 ){
    people++;
  }
  Serial.print("Number of people =");
  Serial.println(people);
  delay(500);
}
