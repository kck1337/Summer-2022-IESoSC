//Cloud computing libraries and set up
#include <WiFiNINA.h>
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "k12stem"
#define AIO_KEY         "e7f0b51f634d4234b065ad78c387c934"

// WiFi setup
char ssid[] = "WIFI_NAME";      // Wifi SSID
char pass[] = "PASSWORD";       // Wifi password

// Initialize the Wifi client
WiFiSSLClient client;

//Defining input sensor pins
int leftFsrPin = A0;
int rightFsrPin = A1;
int pingPin = 7;
//initiating variables
int leftVal = 0;
int rightVal = 0;
long duration = 0;
long inches = 0;
long cm = 0;
int noteDuration = 0;

//These are unsigned integers of 32 bits used for streaming data to Adafruit IO
uint32_t x = 0;
uint32_t y = 0;
uint32_t z = 0;

int8_t ret;

//This is the note that the buzzer will play
#define NOTE_C4  262

// Create a BridgeClient instance to communicate using the Yun's bridge & Linux OS.
BridgeClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup a feed called 'photocell' for publishing.
Adafruit_MQTT_Publish leg1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/leg1");
Adafruit_MQTT_Publish leg2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/leg2");
Adafruit_MQTT_Publish ultrasound = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ultrasound");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial){};
  WiFi.begin(ssid, pass);
  printWifiStatus();
}

void loop() {
  readSensors(); //This function reads all the values from input sensors
  //x,y and z are the variables that will send data to Adafruit IO cloud
  x = leftVal;  
  y = rightVal;
  z = cm;

  MQTT_connect();//This function connects to Adafruit IO and intermittently sends data
  createFeeds(); //This function creates the actual feeds on Adafruit IO cloud service
  checkFull(); //This function checks if the trash can is full 
}

void readSensors(){
  leftVal = analogRead(leftFsrPin);
  rightVal = analogRead(rightFsrPin);
  pingSensor();
}
 
void checkFull(){
  noteDuration = (1000/4);
  if ((cm < 10) || ((leftVal > 960) && (leftVal > 960))) {
    for (int i = 0; i < 5; i++){
      tone(8, NOTE_C4, noteDuration);
      delay((noteDuration * 1.30));
      noTone(8);
    }
  } else {
    noTone(8);
  }
}
 
void MQTT_connect() {
 
  // Stop if already connected.
  if (mqtt.connected()) {
   // Console.println("Connected");
    return;
  }
  Console.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Console.println(mqtt.connectErrorString(ret));
    Console.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(1000);  // wait 1 seconds
  }
  Console.println("MQTT Connected!");
}

void createFeeds(){
  
  if (! leg1.publish(x)) {
    Console.println(F("Failed"));
  } else {
    Console.println(F("OK!"));
  }
  // ping the server to keep the mqtt connection alive
  if (! mqtt.ping()) {
    Console.println(F("MQTT Ping failed."));
  }
  
  if (! leg2.publish(y)) {
    Console.println(F("Failed"));
  } else {
    Console.println(F("OK!"));
  }
  
  if (! mqtt.ping()) {
    Console.println(F("MQTT Ping failed."));
  }
   
  if (! ultrasound.publish(z)) {
    Console.println(F("Failed"));
  } else {
    Console.println(F("OK!"));
  }
  // ping the server to keep the mqtt connection alive
  if (! mqtt.ping()) {
    Console.println(F("MQTT Ping failed."));
  }

}

void pingSensor() {
   // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();
//
//  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP(); // Device IP address
  Serial.print("IP Address: ");
  Serial.println(ip);
