#include "RZDriver.h"

// Constructor to initialize pins
RZDriver::RZDriver(int FI_pin, int BI_pin) {
  _fi_pin = FI_pin;
  _bi_pin = BI_pin;
  init();
}

// Initialization method
void RZDriver::init() {
  pinMode(_fi_pin, OUTPUT);
  pinMode(_bi_pin, OUTPUT);
  analogWrite(_fi_pin, 255);
  analogWrite(_bi_pin, 255);
}

// Method to set the speed
void RZDriver::setSpeed(int speed) {
  if (speed > 255) speed = 255;
  if (speed < -255) speed = -255;
  if (speed > 0) {
    analogWrite(_fi_pin, speed); 
    analogWrite(_bi_pin, 0);
  } else {
    analogWrite(_fi_pin, 0);
    analogWrite(_bi_pin, -speed);
  }
}
