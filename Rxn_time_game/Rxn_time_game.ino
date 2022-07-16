int btn = 2; // Pin for button
int led = 3;  // Pin for Green Led
int led2 = 4; // Pin for white Led
int s = 0;    // Flag 1
int b = 0;    // Flag 2
long t1, t2;  // Time variables

void setup() {
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(A0, INPUT);

}

void loop() {
  while(s == 0){
    int x = analogRead(A0);
    randomSeed(x);
    int rand_num = random(1000, 10000);


    delay(3000);
    digitalWrite(led2, 1);
    delay(rand_num);
    digitalWrite(led2, 0);
    digitalWrite(led, 1);
    t1 = millis();
    while(b == 0){
      int b_state = digitalRead(2);
      if(b_state == 0){
        t2 = millis();
        b = 1;
        }
    }
    long t = t2 - t1;
    if(t < 500){
      digitalWrite(led, 1);
      digitalWrite(led2, 1);
      delay(5000);
    }
    else if(t > 500){
      digitalWrite(led, 1);
      delay(250);
      digitalWrite(led, 0);
      digitalWrite(led2, 1);
      delay(250);
      digitalWrite(led, 1);
      digitalWrite(led2, 0);
      delay(250);
      digitalWrite(led, 0);
      digitalWrite(led2, 1);
    }
    s = 1;
    }
  if(digitalRead(btn) == 0){
    s = 0;
    digitalWrite(led, 0);
    digitalWrite(led2, 0);
  }

}
