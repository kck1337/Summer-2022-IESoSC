/***************************************************
  Adafruit MQTT Library Arduino Nano 33 IoT Example
 ****************************************************/
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiNINA.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>

/************************* WiFI Setup *****************************/
char ssid[] = "HOTSPOT2";     //  your network SSID (name)
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "kck1337"
#define AIO_KEY       "aio_YIDk11GzdYLKaITnuZYFAy4jSX5E"

/************ Global State (you don't need to change this!) ******************/

//Set up the wifi client
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish people_counter = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/people_cntr");

/*************************** Sketch Code ************************************/
uint32_t people = 0;
int fsr_pin = A0;
long prev_time, curr_time;

void setup() {
  while (!Serial);
  WiFi.begin(ssid, pass);
  delay(1000);
  printWifiStatus();
  Serial.begin(115200);
  Wire.begin();
  TSL2561.init();
  pinMode(fsr_pin, INPUT);
  prev_time = millis(); 
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  curr_time = millis();
  MQTT_connect();
  if(curr_time-prev_time >= 5000){
  // Now we can publish stuff!
  Serial.print(F("\nSending People Count "));
  Serial.print(people);
  Serial.print("...");
  if (! people_counter.publish(people)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  prev_time = curr_time;
  }
  int lux = TSL2561.readVisibleLux();
  int weight = analogRead(fsr_pin);
  if(lux < 1000 and weight > 500 ){
    people++;
  }
  Serial.print("Number of people =");
  Serial.println(people);
  delay(500);
}

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
