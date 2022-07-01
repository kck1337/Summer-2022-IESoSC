/***************************************************
  Adafruit MQTT Library and Arduino Nano 33 IoT for Cloud integration of people counter
 ****************************************************/
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiNINA.h>
#include <Wire.h>
#include <Digital_Light_ISL29035.h>
#include <Digital_Light_TSL2561.h>
/************************* WiFI Setup *****************************/
char ssid[] = "WIFI_NAME";     //  your network SSID (name)
char pass[] = "PASSWORD";    // your network password (use for WPA, or use as key for WEP)

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  ""  // copy from adafruit IO
#define AIO_KEY       "" // copy from adafruit IO

/************ Global State (you don't need to change this!) ******************/

//Set up the wifi client
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

/****************************** Feeds ***************************************/

// Setup a feed for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish laser_cntr = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/laser_cntr");
Adafruit_MQTT_Publish peizo_cntr = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/peizo_cntr");
/*************************** Functions ************************************/
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP(); // Device IP address
  Serial.print("IP Address: ");
  Serial.println(ip);
}
/*************************** Sketch Code ************************************/
// define more variables as needed
uint32_t x=0;
int knockSensor = A0;
byte val = 0;
int Threshold = 7;
uint32_t laserCounter;
int prevSensor = 1023;
int statePin = LOW;
int prev_val = 3;
uint32_t peizoCounter;
unsigned long prev_time = 0;
unsigned long curr_time = 0;

void setup() {
  while (!Serial);
  Wire.begin();
  TSL2561.init();
  WiFi.begin(ssid, pass);
  delay(1000);
  printWifiStatus();
  Serial.begin(115200);
}

void loop() {
  // Track run time to limit data upload rate
  prev_time = millis();

  // Run indefeinte loop 
  while(true){
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  // Now we can publish stuff!

  // Publish data every 10 seconds
  if(curr_time - prev_time >= 10000){
    if(! laser_cntr.publish(laserCounter)){
      Serial.println(F("Laser update Failed"));
      }
    else{
      Serial.println(F("Laser update OK"));    
        }
    if(! peizo_cntr.publish(peizoCounter)){
      Serial.println(F("Peizo update Failed"));
      }
    else{
      Serial.println(F("Peizo update OK"));    
        }
    prev_time = curr_time;

    }
// Laser counter
Serial.println("-----Laser as laserCounter-----");
  int sensor = TSL2561.readVisibleLux();
  Serial.print("The light value is: ");
  Serial.println(TSL2561.readVisibleLux());

  if(sensor<1000 and prevSensor>1000){
    laserCounter = laserCounter+1;
    Serial.print("Count of people is: ");
    Serial.println(laserCounter);
  }
  else{
    Serial.println(laserCounter);
  }
  prevSensor = sensor;

// Peizo counter
  Serial.println("-----Piezo as laserCounter-----");
  val = analogRead(knockSensor);
  Serial.print("Piezo sensor value is: ");
  Serial.println(val);

  if(val >= Threshold and prev_val <= Threshold){
    peizoCounter = peizoCounter + 1;
    Serial.println("Knock!");
    Serial.println(peizoCounter);
    delay(100);
  }
  prev_val = val;
  delay(100);

  // current time to track run time
  curr_time = millis();
  }
}
