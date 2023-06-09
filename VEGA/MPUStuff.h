#include <Wire.h>
#include <TinyMPU6050.h>

TwoWire Wire(1);
MPU6050 mpu(Wire);

float prev_yaw;
float smoothing_factor = 0.8;

void SetupMPU(){
  Serial.println("INITIALIZING MPU");
  mpu.Initialize();
  Serial.println(F("CALIBRATING MPU, DONOT MOVE"));
  delay(500);
  mpu.Calibrate();
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());
  Serial.println("Calibration complete!");
  Time = micros(); 
}

void ReadFromMPU() {
  mpu.Execute();
                               
  timePrev = Time;
  Time = micros();
  elapsedTime = (float)(Time - timePrev) / (float)1000000;

  if (elapsedTime == 0) {return;}
  
  angle_roll = mpu.GetAngY();
  angle_pitch = mpu.GetAngX();
  angle_yaw = mpu.GetAngZ();

  float delta_yaw = angle_yaw * 0.5 - prev_yaw * 0.5;
  prev_yaw = angle_yaw;
  
  ESCout_1 = input_THROTTLE - angle_roll + angle_pitch + delta_yaw;
  ESCout_2 = input_THROTTLE + angle_roll + angle_pitch - delta_yaw;
  ESCout_3 = input_THROTTLE - angle_roll - angle_pitch + delta_yaw;
  ESCout_4 = input_THROTTLE + angle_roll - angle_pitch - delta_yaw;
  
  if(ESCout_1>maxThrottle) ESCout_1=maxThrottle;
  else if(ESCout_1<minThrottle) ESCout_1=minThrottle;
  
  if(ESCout_2>maxThrottle) ESCout_2=maxThrottle;
  else if(ESCout_2<minThrottle) ESCout_2=minThrottle;
  
  if(ESCout_3>maxThrottle) ESCout_3=maxThrottle;
  else if(ESCout_3<minThrottle) ESCout_3=minThrottle;
  
  if(ESCout_4>maxThrottle) ESCout_4=maxThrottle;
  else if(ESCout_4<minThrottle) ESCout_4=minThrottle;

 
    Serial.print(">");
    Serial.print(angle_roll);Serial.print(" R ");
    Serial.print(angle_pitch);Serial.print(" P ");
    Serial.print(delta_yaw);Serial.println(" Y ");
  
}
