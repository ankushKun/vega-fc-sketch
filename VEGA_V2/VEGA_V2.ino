#include "GLOBALS.h"
#include "IMU.h"
#include "RECEIVER.h"
#include "PID.h"
#include "MOTOR.h"

void setup() {
  Serial.println("\n\nBOOTED");
  SetupIMU();
  SetupRECEIVER();
  SetupMOTOR();
  Serial.println("SETUP COMPLETE");
}

void loop() {
  LoopIMU();
  Serial.print("Roll Angle [°] ");
  Serial.print(KalmanAngleRoll);
  Serial.print(" Pitch Angle [°] ");
  Serial.println(KalmanAnglePitch);

  LoopRECEIVER();
//  Serial.print("THROTTLE ");Serial.print(throttleRaw);
//  Serial.print(" ROLL ");Serial.print(rollRaw);
//  Serial.print(" PITCH ");Serial.print(pitchRaw);
//  Serial.print(" YAW ");Serial.println(yawRaw);
//  Serial.print(" KILL ");Serial.print(killRaw);
//  Serial.print(" MODE ");Serial.print(modeRaw);
//  Serial.print(" BTN ");Serial.println(btnRaw);

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
  
  while (micros() - LoopTimer < 4000);
  LoopTimer=micros();
}
