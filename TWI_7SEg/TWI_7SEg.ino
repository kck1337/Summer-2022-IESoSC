#include <TM1637.h>
int CLK = 2;
int DIO = 3;

TM1637 tm(CLK, DIO);

void setup() {
//nitialize display
  tm.init();

  // Set Brightness
  tm.set(7);
}

void loop() {
for(int i = 0; i<10000;i++){
  displayNumber(i) ;
  delay(1000);
}
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
