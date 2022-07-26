const int ls = A0;
const int rs = A1;

void setup() {
  pinMode(ls, 1);
  pinMode(rs, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
int x = analogRead(ls);
int y = analogRead(rs);

Serial.print(x);
Serial.print("\t");
Serial.println(y);
}
