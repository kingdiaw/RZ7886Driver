# RZDriver Arduino Library

The **RZDriver** library is an Arduino library designed to control the RZ7886 motor driver. This library allows for easy control of motor speed and direction using simple commands.

## Features

- Easy-to-use interface for controlling motor speed and direction.
- Supports both forward and backward motion.
- Simple installation and integration with Arduino projects.

## Getting Started

### Prerequisites

- Arduino IDE (version 1.8.13 or higher)
- An Arduino-compatible board (e.g., ESP32)
- RZ7886 motor driver

### Installation

1. **Clone the Repository**

   To download the library, clone this repository into your Arduino libraries folder. Open a terminal and run the following command:

```bash
   git clone https://github.com/kingdiaw/RZ7886Driver.git
```

## Usage

### Include the Library in Your Sketch

Start by including the `RZDriver` library in your Arduino sketch:

```cpp
#include <RZDriver.h>
```
### Create an Instance of RZDriver

Initialize the motor driver by specifying the pins connected to the RZ7886 driver's forward and backward input pins:

```cpp
RZDriver motor(9, 10); // Replace 9 and 10 with your actual pin numbers
```
### Set the Motor Speed

Use the **setSpeed** function to control the motor speed and direction:

```cpp
void setup() {
    // Set motor speed to full forward
    motor.setSpeed(255);
}

void loop() {
    // Change motor speed or direction as needed
    motor.setSpeed(-100); // Move motor backward at partial speed
    delay(1000);
    motor.setSpeed(0); // Stop the motor
    delay(1000);
}
```
**`setSpeed(int speed)`**: Accepts values from -255 to 255. Positive values move the motor forward, and negative values move the motor backward.

## Example

The `examples` folder contains an example sketch demonstrating how to use the RZDriver library. Open the `ESP32_RZ_Basic` example in the Arduino IDE:

1. Go to **File > Examples > RZDriver > ESP32_RZ_Basic**.
2. Upload the example to your Arduino board.
