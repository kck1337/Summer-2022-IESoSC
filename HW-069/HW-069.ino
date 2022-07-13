#include <TM1637.h>

int CLK = 2;
int DIO = 3;

TM1637 tm(CLK,DIO);

void setup() {
  // put your setup code here, to run once:
  tm.init();

  //set brightness; 0-7
  tm.set(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  // example: "12:ab"
  // tm.display(position, character);
  tm.display(0,12);
  tm.display(1,13);
  tm.point(1);
  tm.display(2,14);
  tm.display(3,15);

  delay(3000);

  // example: "1234"
  displayNumber(1234);

  delay(1000);
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
