
#include <Wire.h>
TwoWire Wire(0);
#include "GLOBALS.h"
#include "OLED.h"
#include "WIFI.h"
#include "IMU.h"
#include "RECEIVER.h"
#include "PID.h"
#include "MOTOR.h"

long lastRecieved;
void setup() {
  Serial.println("\n\nBOOTED");
  SetupOLED();
  SetupWIFI();
  SetupIMU();
  SetupRECEIVER();
  SetupMOTOR();
  Serial.println("SETUP COMPLETE");
  oledPrint("SETUP\nCOMPLETE",2,true,true,true);
  lastRecieved = micros();
}

void loop() {
  for(int i=0;i<3                                                                                                                  ;i++){
    mpu.update();
    delay(3);
  }
  LoopIMU();

  Serial.print(">");
  Serial.print(AngleRoll);
  Serial.print(" R ");
  Serial.print(AnglePitch);
  Serial.print(" P ");
  Serial.print(AngleYaw);
  Serial.println(" Y ");

  if(micros() - lastRecieved > (100*1000)){
    LoopRECEIVER();
    lastRecieved = micros();
  }

  Serial.print("THROTTLE ");Serial.print(throttleRaw);
  Serial.print(" ROLL ");Serial.print(rollRaw);
  Serial.print(" PITCH ");Serial.print(pitchRaw);
  Serial.print(" YAW ");Serial.print(yawRaw);
  Serial.print(" KILL ");Serial.print(killRaw);
  Serial.print(" MODE ");Serial.print(modeRaw);
  Serial.print(" BTN ");Serial.println(btnRaw);

  LoopPID();

  Serial.print("THROTTLE ");Serial.print(input_THROTTLE);
  Serial.print(" ROLL ");Serial.print(input_ROLL);
  Serial.print(" PITCH ");Serial.print(input_PITCH);
  Serial.print(" YAW ");Serial.println(input_YAW);
  
  LoopMOTOR();
  Serial.print("ESC3 ");Serial.print(ESCout_3);
  Serial.print(" ESC1 ");Serial.println(ESCout_1);
  Serial.print("ESC2 ");Serial.print(ESCout_2);
  Serial.print(" ESC4 ");Serial.println(ESCout_4);

  LoopWIFI();

  // Refresh OLED 4 times a second
  if(micros() - oledTimer > 250 * 1000){
    display.display();
    oledTimer = micros();
  }
}
