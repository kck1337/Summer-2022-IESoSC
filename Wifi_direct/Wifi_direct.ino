#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "WIFI_NAME";      // Wifi SSID
char pass[] = "PASSWORD";       // Wifi password

// Initialize the Wifi client
WiFiSSLClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial){};
  WiFi.begin(ssid, pass);
  printWifiStatus();
}

void loop() {
  // put your main code here, to run repeatedly:
//  int x = analogRead(A0);
//  Serial.println(x);

}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP(); // Device IP address
  Serial.print("IP Address: ");
  Serial.println(ip);
}
