#include <Servo.h>

Servo left;
Servo right;

void setup() {
  left.attach(9);
  right.attach(10);
//  Serial.begin(9600);
//  while(!Serial);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

}

int data1 = 0;
int data2 = 0; 

void loop() {
  stop();
  int x = analogRead(A0);
  int y = analogRead(A1);
  int dr = map(x, 0, 1023, -100, 100);
  dr = dr * 0.4 + (data1 * 0.6);
  int tr = map(y, 0, 1023, -100, 100);
  tr = tr * 0.4 + (data2 * 0.6);
//  Serial.print(dr);
//  Serial.print(",");
//  Serial.println(tr);
//  Serial.print("\t");
//  Serial.println(vec);
//  delay(1);

  if(dr > 10){
    drive();
    }
  else if(dr < -10){
    back();
  }
  
}


void stop(){
  left.write(90);
  right.write(90);
  }
void drive(){
  left.write(110);
  right.write(60);
  }
void back(){;
  left.write(85);
  right.write(95);
  }
  
