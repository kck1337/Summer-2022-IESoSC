int knockSensor = A0;
byte val = 0;
int threshold = 190;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(knockSensor);
//  Serial.println(val);
  if(val >= threshold){
    Serial.println("Knocked");
//      Serial.println(val);
    }
  delay(100);
}
