#include <ArduinoBLE.h>

//on terminal, use [uuidgen] to get a randomly-generated ID
//use the ID as serviceUUID and change 1 character and use as charUUID
//copy the serviceUUID into the serviceUUID JavaScript variable as well
#define serviceUUID "3c5bd4c2-055f-11ed-b939-0242ac120002"
#define charUUID "4c5bd4c2-055f-11ed-b939-0242ac120002"

//String carName = "Hehe"; //name your car whatever you want

BLEService moveCar(serviceUUID);
BLEIntCharacteristic dir(charUUID, BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  while (!BLE.begin()) {
    Serial.println("Error initializing BLE...");
    delay(2000);
  }
  Serial.println("BLE initialized!");
  BLE.setLocalName("Hehe"); 
  BLE.setAdvertisedService(moveCar);
  moveCar.addCharacteristic(dir);
  BLE.addService(moveCar);
  BLE.advertise();
}

bool centralConnected = false;

void loop() {
  BLEDevice central = BLE.central();
  if (central && !centralConnected) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    centralConnected = true;
  } else if (!central && centralConnected) {
    Serial.println("Disconnected from central.");
    centralConnected = false;
  }

  if (central.connected() && central) {
    if (dir.written()) {
//      moveCar(dir.value());
      Serial.println("BLE received:");
      Serial.println(dir.value());
    }
  }
}

//void moveCar(int num) {
//  if (int == 0) {
//    
//  } else if (int == 1) {
//    
//  }
//  //etc...
//}
