// Define pins for each colour
int Red = 3; 
int Blue = 4;
int Green = 2;

// Set pin direction 
void setup() {
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
}

// Turn each colour on for 1 second and off in 1/4th of second
void loop() {
  digitalWrite(Red, HIGH);
  delay(1000);
  digitalWrite(Red, LOW);
  delay(250);
  digitalWrite(Green, HIGH);
  delay(1000);
  digitalWrite(Green, LOW);
  delay(250);
  digitalWrite(Blue, HIGH);
  delay(1000);
  digitalWrite(Blue, LOW);
  delay(250);
}
