#include "_GLOBAL.h"
#include "BLDC.h"
#include "MPUStuff.h"
#include "WiFi.h"

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println(">>> BOOTED");

//  SetupESC();
//  CalibrateESC();
//  delay(500);
//  SetupMPU();
//  delay(500);
  SetupWifi();
  delay(500);
  Time = micros();
}

void loop() {
  CheckUDP();
//  Oscillate();
//  ReadFromMPU();
//  WriteESC();
//  Serial.println();
}
