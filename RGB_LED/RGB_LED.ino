// Define pins for each colour
int Red = 3; 
int Blue = 4;
int Green = 2;

// Set pin direction 
void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  digitalWrite(Red, HIGH);
  digitalWrite(Green, HIGH);
  digitalWrite(Blue, HIGH);
}

// Turn each colour on for 1 second and off in 1/4th of second
void loop() {
  digitalWrite(Red, LOW);
  delay(1);
  digitalWrite(Red, HIGH);
  delay(1);
  digitalWrite(Green, LOW);
  delay(1);
  digitalWrite(Green, HIGH);
  delay(1);
  digitalWrite(Blue, LOW);
  delay(1);
  digitalWrite(Blue, HIGH);
  delay(1);
}
