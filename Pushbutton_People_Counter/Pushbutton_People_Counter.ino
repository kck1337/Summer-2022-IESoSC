int p_in = 0;
int p_out = 0;
int tot = 0;

void setup() {
 pinMode(2, INPUT_PULLUP);
 pinMode(3, INPUT_PULLUP);
 Serial.begin(9600);
}

void loop() {
  delay(100);
  int x = digitalRead(2);
  int y = digitalRead(3);

  if(x == 0){
    p_out++;
    }
  if(y == 0){
    p_in++;
    }

    
  Serial.print("People in:");
  Serial.print(p_in);
  Serial.print("\t");
  Serial.print("People out:");
  Serial.print(p_out);
  Serial.print("\t");
  Serial.print("Total inside:");
  Serial.println(p_in-p_out);
  
}
