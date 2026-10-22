#include <RZDriver.h>
#include "pitches.h"

#define FI_1 25
#define BI_1 26
#define FI_2 27
#define BI_2 14

#define CH1_PIN 32  
#define CH2_PIN 33   

#define BUZ_PIN 15

RZDriver motor1(FI_2, BI_2);  
RZDriver motor2(FI_1, BI_1);  


int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// Parameter kawalan
const int DEADZONE = 30;
//const int MAX_INPUT = 400;
const int MAX_MOTOR_SPEED = 255;

void setup() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(15, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(15);
  }

  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("Test Robot");

}

void loop() {
  // Baca input dari receiver
  int ch1_us = pulseIn(CH1_PIN, HIGH, 25000);  // Steering
  int ch2_us = pulseIn(CH2_PIN, HIGH, 25000);  // Throttle

  if (ch1_us == 0 || ch2_us == 0) {
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    return;
  }
  // Kira offset dari tengah (1500µs)
  int steer = ch1_us - 1500;
  int throttle = ch2_us - 1500;

  // Deadzone
  if (abs(steer) < DEADZONE) steer = 0;
  if (abs(throttle) < DEADZONE) throttle = 0;

  // Pemetaan nilai input
  steer = constrain(steer, -MAX_INPUT, MAX_INPUT);
  throttle = constrain(throttle, -MAX_INPUT, MAX_INPUT);

  // Normalisasi
  float normSteer = (float)steer / MAX_INPUT;
  float normThrottle = (float)throttle / MAX_INPUT;

  // 🚀 BOOST: Gandakan throttle ke depan (0.0 ke 0.5 jadi 0.0 ke 1.0)
  if (normThrottle > 0) {
    normThrottle = normThrottle * 2.0;
    normThrottle = constrain(normThrottle, 0.0, 1.0);
  }

  // Campuran kawalan throttle dan steering
  float leftPower = normThrottle + normSteer;
  float rightPower = normThrottle - normSteer;

  // Clamp nilai
  leftPower = constrain(leftPower, -1.0, 1.0);
  rightPower = constrain(rightPower, -1.0, 1.0);

  // Skala ke motor speed
  int motor1Speed = (int)(leftPower * MAX_MOTOR_SPEED);
  int motor2Speed = (int)(rightPower * MAX_MOTOR_SPEED);

  // Kawal motor
  motor1.setSpeed(motor1Speed);
  motor2.setSpeed(motor2Speed);

  // Papar debug info
  Serial.print("Throttle: ");
  Serial.print(throttle);
  Serial.print(" | Steer: ");
  Serial.print(steer);
  Serial.print(" | M1: ");
  Serial.print(motor1Speed);
  Serial.print(" | M2: ");
  Serial.println(motor2Speed);

  delay(50);
}