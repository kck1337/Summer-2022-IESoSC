int counter = 10;     // Countdown variable
void setup() {
  Serial.begin(9600); // Start serial communication
  while(!Serial);     // Do nothing while the serial monitor is not open
}

void loop() {
while(counter >= 0){  // While counter is greater than zero
  if(counter == 0){   // If counter reaches zero
    Serial.println("WAIT!!!");  // Print Wait
    }
  Serial.println(counter);      // Print counter number
  counter--;          // Decrease counter by 1
  delay(1000);        // Pause for 1 sec or 1000 milliseconds
  }
}
