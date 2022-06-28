int score = 0;

void setup() {
   Serial.begin(9600);  // Start Serial Communitcation  
}

void loop() {
     if (Serial.available() > 0)  // Check if serial monitor is open
     {
      score = Serial.parseInt();  // Assign the input to variable score
      delay(500);                 // Pause for half a second or 500 ms
      if (score >= 90)            // If score is greater than or equal to 90
      {
        Serial.print("Your grade is A \n");
      }
      else if (score >= 80 && score < 90)   // If score is greater than or equal to 80 or less than 90
      {
        Serial.print("Your grade is B \n");
      }
      else if (score >= 70 && score < 80)   // If score is greater than or equal to 70 or less than 80
      {
        Serial.print("Your grade is C \n");
      }
      else                                  // If score is less than 70
      {
        Serial.print("Your grade is D \n");   
      }
    }
}
