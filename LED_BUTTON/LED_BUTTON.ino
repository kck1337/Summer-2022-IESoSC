const int ledPin = 2;
const int btnPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btnPin)==HIGH){
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  }
