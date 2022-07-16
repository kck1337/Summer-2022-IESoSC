#include <Servo.h>

//Servo left;
Servo right;

void setup() {
//  left.attach(2);
  right.attach(3);
  Serial.begin(9600);
  while(!Serial);
  pinMode(2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT_PULLUP);

}

int data1 = 0;
int data2 = 0; 

void loop() {
  delay(1);
  stop();
  int x = analogRead(A0);
  int y = digitalRead(A1);
//  x = x * 0.4 + (data1 * 0.6);
//  y = y * 0.4 + (data2 * 0.6);
  int dr = map(x, 0, 1023, -100, 100);
//  int tr = map(y, 0, 1023, -100, 100);
  
  if(y == 0){
    drive();
    }
  else if(y == 1){
    back();
  }
  
  Serial.print(dr);
  Serial.print(",");
  Serial.println(y);
//  Serial.print("\t");
//  Serial.println(vec);
//  delay(1);

  
}


void stop(){
//  left.write(90);
//  right.write(90);
analogWrite(2, 0);
analogWrite(3, 0);
  }
void drive(){
//  left.write(100);
//  right.write(80);
//analogWrite(2, 128);
//analogWrite(3, 128);
digitalWrite(2, HIGH);
delayMicroseconds(1700);
digitalWrite(2, LOW);
delayMicroseconds(20000);
  }
void back(){;
//  left.write(85);
  right.write(95);
  }
  
