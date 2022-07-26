/***************************************************
  Adafruit MQTT Library Arduino Nano 33 IoT Example
 ****************************************************/
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiNINA.h>
#include <math.h>


#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif

/************************* WiFI Setup *****************************/
char ssid[] = "TP-Link_7F89";     //  your network SSID (name)
char pass[] = "weindianBOIS";    // your network password (use for WPA, or use as key for WEP)

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "kck1337"
#define AIO_KEY       "aio_gdff338ZnGULFEqJ5mPwu8QZoSQb"

/************ Global State (you don't need to change this!) ******************/

//Set up the wifi client
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish feedname = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");
/*************************** Sketch Code ************************************/
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0
uint32_t temperature = 0;
long curr_time, prev_time;

/***************************************************************************/


void setup() {
//  while (!Serial);
  WiFi.begin(ssid, pass);
  delay(1000);
  printWifiStatus();
  Serial.begin(115200);  
  prev_time = millis();
  pinMode(13,1);
}



void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  curr_time = millis();
  MQTT_connect();
  // Now we can publish stuff!
  if(curr_time - prev_time >= 5000){
    digitalWrite(13,1);
  Serial.print(F("\nSending Temperature value: "));
  Serial.print(temperature);
  Serial.print("...");
  if (! feedname.publish(temperature)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
  prev_time = curr_time;
  delay(150);
  digitalWrite(13,0);
  }
  int a = analogRead(pinTempSensor);
 
    float R = 1023.0/a-1.0;
    R = R0*R;
 
    temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
 
    Serial.print("temperature = ");
    Serial.println(temperature);
 
    delay(100);
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
