int pir_1 = 3;
int pir_2 = 4;
int val_1, val_2;



void setup() {
  pinMode(pir_1, INPUT);
  pinMode(pir_2, INPUT);

  Serial.begin(9600);
}

void loop() {
  val_1 = digitalRead(pir_1);
  val_2 = digitalRead(pir_2);


  if(val_1 == 1){
    Serial.println("Sensor 1 motion detected");
    }
  if(val_2 == 1){
    Serial.println("Sensor 2 motion detected");
    }

  delay(500);
}
