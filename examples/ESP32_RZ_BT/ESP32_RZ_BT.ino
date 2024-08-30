#include <RZDriver.h>
#include "BluetoothSerial.h"

#define FI_1 25
#define BI_1 26
#define FI_2 27
#define BI_2 14

String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
RZDriver motorA(FI_1, BI_1);
RZDriver motorB(FI_2, BI_2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    switch (command) {
      case 'F':  // Move Forward
        motorA.setSpeed(255);
        motorB.setSpeed(255);
        break;
      case 'B':  // Move Backward
        motorA.setSpeed(-255);
        motorB.setSpeed(-255);
        break;
      case 'L':  // Turn Left
        motorA.setSpeed(-255);
        motorB.setSpeed(255);
        break;
      case 'R':  // Turn Right
        motorA.setSpeed(255);
        motorB.setSpeed(-255);
        break;
      case 'S':  // Stop
        motorA.setSpeed(0);
        motorB.setSpeed(0);
        break;
      default:
        motorA.setSpeed(0);
        motorB.setSpeed(0);
        break;
    }
  }
  delay(20); // Small delay for stability
}

