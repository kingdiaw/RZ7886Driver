#include <RZDriver.h>

#define CH1_PIN 32  
#define CH2_PIN 33 

RZDriver motor1(27, 14);  
RZDriver motor2(25, 26);  

void setup() {
  // put your setup code here, to run once:
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);
  pinMode (15, OUTPUT);
  digitalWrite(15,LOW);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int steer = pulseIn(CH1_PIN, HIGH, 25000);  
  int throttle = pulseIn(CH2_PIN, HIGH, 25000);  

  Serial.print("Steer:");
  Serial.print(steer);
  Serial.print("\tThrottle:");
  Serial.println(throttle);
  delay(200);
}
