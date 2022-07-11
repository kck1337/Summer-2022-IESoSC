int a=0, b=0; 
float d=0;
int sym;
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Enter the 1st number\n");
  Serial.print("Enter the 2nd number \n");
  Serial.print("Enter the operation 1 is +, 2 is -, 3 is *, and 4 is / \n");
}

void loop() {
  if(Serial.available() > 0){
    a = Serial.parseInt();
    Serial.print("1st Number is:");
    Serial.println(a);
    b = Serial.parseInt();
    Serial.print("2nd Number is:");
    Serial.println(b);
    sym = Serial.parseInt();
    d = calc(a, b, sym);
    Serial.print("Answer is:");  
    Serial.println(c);
    }

}

int calc(int a, int b, int sym){
  if(sym == 1){
    Serial.print("Symbol is:");
    Serial.println("+");
    int c = a + b;
    return c;
    }
  else if(sym == 2){
    Serial.print("Symbol is:");
    Serial.println("-");
    int c = a - b;
    return c;
    }
  else if(sym == 3){
    Serial.print("Symbol is:");
    Serial.println("*");
    int c = a * b;
    return c;
    }
  else if(sym == 4){
    Serial.print("Symbol is:");
    Serial.println("/");
    float c = a / b;
    return c;
    }
  else
  {
    Serial.println("invalid operation");  
  }
  }
