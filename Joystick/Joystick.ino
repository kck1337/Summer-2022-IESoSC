void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

}

int data1 = 0;
int data2 = 0; 

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int dr = map(x, 0, 1023, -100, 100);
  dr = dr * 0.4 + (data1 * 0.6);
  int tr = map(y, 0, 1023, -100, 100);
  tr = tr * 0.4 + (data2 * 0.6);
//  int vec = vector(dr, tr);
  Serial.print(dr);
  Serial.print(",");
  Serial.println(tr);
//  Serial.print("\t");
//  Serial.println(vec);
  delay(1);

}


int vector(int dr, int tr){
  int vec = (100*dr)+(tr);
  return vec;
  }
