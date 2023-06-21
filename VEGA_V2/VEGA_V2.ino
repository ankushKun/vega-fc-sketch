#include <Wire.h>
TwoWire Wire(0);
#include "GLOBALS.h"
#include "OLED.h"
#include "IMU.h"
#include "RECEIVER.h"
#include "PID.h"
#include "MOTOR.h"

long lastRecieved;
void setup() {
  Serial.println("\n\nBOOTED");
  SetupOLED();
  SetupIMU();
  SetupRECEIVER();
  SetupMOTOR();
  Serial.println("SETUP COMPLETE");
  oledPrint("SETUP\nCOMPLETE",2,true,true,true);
  lastRecieved = micros();
}

void loop() {
  for(int i=0;i<10;i++){
    mpu.update();
    delay(3); 
  }
  LoopIMU();

  if(micros() - lastRecieved > (80*1000)){
    LoopRECEIVER();
    lastRecieved = micros();
  }
  
  Serial.print("Roll ");
  Serial.print(AngleRoll);
  Serial.print(" Pitch ");
  Serial.print(AnglePitch);
  Serial.print(" Yaw ");
  Serial.println(AngleYaw);

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

  // Refresh OLED 4 times a second
  if(micros() - oledTimer > 200 * 1000){
    display.display();
    oledTimer = micros();
  }
}
