int fsr1 = A0;
int fsr2 = A1;

void setup() {
  pinMode(fsr1, INPUT);
  pinMode(fsr2, INPUT);

}

void loop() {
  int r1 = analogRead(fsr1);
  int r2 = analogRead(fsr2);

//  Serial.print(r1);
//  Serial.print("\t");
  Serial.println(r1);

}
