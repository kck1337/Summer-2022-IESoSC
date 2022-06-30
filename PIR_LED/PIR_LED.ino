int pir_1 = 3;
int pir_2 = 4;
int led_1 = 5;
int led_2 = 6;

int val_1, val_2;

void setup() {
  pinMode(pir_1, INPUT);
  pinMode(pir_2, INPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  val_1 = digitalRead(pir_1);
  val_2 = digitalRead(pir_2);
  if(val_1 == 1){
    digitalWrite(led_1, HIGH);
    Serial.println("Sensor 1 motion detected");
    }
  if(val_2 == 1){
    digitalWrite(led_2, HIGH);
    Serial.println("Sensor 2 motion detected");
    }
  delay(500);
}
