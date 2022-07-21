#include <ArduinoBLE.h>
#include <Servo.h>

//on terminal, use [uuidgen] **On Mac or Linux** to get a randomly-generated ID
//use the ID as serviceUUID and change 1 character and use as charUUID
//copy the serviceUUID into the serviceUUID JavaScript variable as well

#define serviceUUID "3c5bd4c2-055f-11ed-b939-0242ac120002"
#define charUUID "4c5bd4c2-055f-11ed-b939-0242ac120002"

//String carName = "Hehe"; //name your car whatever you want

BLEService moveCar(serviceUUID);
BLEIntCharacteristic dir(charUUID, BLERead | BLEWrite);

int lm = 2; // Motor pins
int rm = 3;

Servo left; // Can change
Servo right;

void setup() {
  left.attach(2); // can change 
  right.attach(3);
  left.write(90);
  right.write(90);
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
      Serial.println("BLE received:");
      Serial.println(dir.value());
      int i = dir.value();
      drive(i);
    }
  }
}

void drive(int x) {
  if(x == 0){
    left.write(90);
    right.write(90);
    }
  else if (x == 1) {
    left.write(100);
    right.write(80);
  }
  else if (x == 2) {
    left.write(80);
    right.write(100);
  }
  else if(x == 3){
    left.write(80);
    right.write(80);    
    }
  else if(x == 4){
    left.write(100);
    right.write(100); 
    }
  else{
    left.write(90);
    right.write(90);
    }
}
