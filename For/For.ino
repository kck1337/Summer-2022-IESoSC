
const int ledPin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int k = 10; k >= 0; k--){
    Serial.print("Time remaining:");
    Serial.println(k);
    delay(1000);
    }

    Serial.print("Wait!!!");
    delay(5000);
}
