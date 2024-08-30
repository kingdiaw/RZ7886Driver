#include <RZDriver.h>

RZDriver m1(25, 26); // Initialize with FI=25 and BI=26

void setup() {
  // Nothing needed here as init is called in the constructor
}

void loop() {
  m1.setSpeed(100); // Set forward speed
  delay(2000);
  m1.setSpeed(-100); // Set backward speed
  delay(2000);
  m1.setSpeed(0); // Stop
  delay(2000);
}
