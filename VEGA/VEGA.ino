#include <Wire.h>
TwoWire Wire(0);

#include "GLOBALS.h"
#include "OLED.h"
#include "Reciever.h"
#include "BLDC.h"
#include "MPUStuff.h"
#include "WiFi.h"

//unsigned long timer = 0;

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println("\n\nBOOTED");

  SetupOLED();
  delay(1000);
  SetupReciever();
  delay(1000);
  SetupWifi();
  delay(1000);
//  CalibrateReciever();
  SetupMPU();
  delay(1000);
  SetupESC();
  delay(1000);
}

void loop() {
  ReadReciever();
//  ReadESP();
  ReadFromMPU();
  WriteESC();

#ifdef DEBUG
  Serial.print(">");
  Serial.print(angle_roll);Serial.print(" R ");
  Serial.print(angle_pitch);Serial.print(" P ");
  Serial.print(angle_yaw);Serial.println(" Y ");
//  Serial.print(delta_yaw);Serial.println(" Y ");
//  Serial.print("Yaw mapped: ");Serial.println(yaw_mapped);
//  Serial.println();

//  Serial.print("ESC3: ");Serial.print(ESCout_3);
//  Serial.print("  ESC1: ");Serial.println(ESCout_1);
//  Serial.print("ESC2: ");Serial.print(ESCout_2);
//  Serial.print("  ESC4: ");Serial.println(ESCout_4);
//
//  Serial.print("TR: ");Serial.print(throttleRaw);
//  Serial.print("  RR: ");Serial.print(rollRaw);
//  Serial.print("  PR: ");Serial.print(pitchRaw);
//  Serial.print("  YR: ");Serial.println(yawRaw);
//  
//  Serial.print("T: ");Serial.print(input_THROTTLE);
//  Serial.print("  R: ");Serial.print(input_ROLL);
//  Serial.print("  P: ");Serial.print(input_PITCH);
//  Serial.print("  Y: ");Serial.println(input_YAW);
  
//  Serial.println();
#endif
//delay(3);
delay(10);
//delayMicroseconds(4000);
}
