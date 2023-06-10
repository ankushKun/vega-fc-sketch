#include "_GLOBAL.h"
#include "BLDC.h"
#include "MPUStuff.h"
#include "WiFi.h"

unsigned long timer = 0;

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println(">>> BOOTED");

  SetupMPU();
  delay(500);
//  SetupWifi();
//  delay(500);
  SetupESC();
  delay(500);
}

void loop() {
//  CheckUDP();
  ReadFromMPU();
  WriteESC();
  delay(10);

#ifdef DEBUG
  Serial.print(">");
  Serial.print(angle_roll);Serial.print(" R ");
  Serial.print(angle_pitch);Serial.print(" P ");
  Serial.print(delta_yaw);Serial.println(" Y ");
  Serial.print("Yaw mapped: ");Serial.println(yaw_mapped);

  Serial.print("ESC3: ");
  Serial.print(ESCout_3);
  Serial.print("\tESC1: ");
  Serial.println(ESCout_1);
  Serial.print("ESC2: ");
  Serial.print(ESCout_2);
  Serial.print("\tESC4: ");
  Serial.println(ESCout_4);
#endif
}
