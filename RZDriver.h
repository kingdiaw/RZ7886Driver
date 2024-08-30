#ifndef RZDRIVER_H
#define RZDRIVER_H

#include <Arduino.h>

class RZDriver {
  private:
    int _fi_pin;
    int _bi_pin;

  public:
    // Constructor to initialize pins
    RZDriver(int FI_pin, int BI_pin);

    // Initialization method
    void init();

    // Method to set the speed
    void setSpeed(int speed);
};

#endif
