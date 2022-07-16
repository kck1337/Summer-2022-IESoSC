int rand_num;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));
}

void loop() {
  rand_num = random(1000, 10000);
  Serial.println(rand_num);

  delay(3000);
}
