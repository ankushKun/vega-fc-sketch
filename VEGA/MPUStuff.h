#include <Wire.h>
#include <TinyMPU6050.h>

TwoWire Wire(1);
MPU6050 mpu(Wire);

float prev_yaw;
float smoothing_factor = 0.8;

long mapf(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
  
  angle_roll = mpu.GetAngY();
  angle_pitch = mpu.GetAngX();
  angle_yaw = mpu.GetAngZ();

  float delta_yaw = (angle_yaw - prev_yaw) * 0.8;
  prev_yaw = angle_yaw;

  if(angle_roll < -100 || angle_pitch < -100){crashed = true;}
  if(crashed)return;

  int roll_mapped = map(angle_roll, -90,90,-40,40);
  int pitch_mapped = map(angle_pitch, -90,90,-40,40);
  int yaw_mapped = mapf(delta_yaw, -2.0,2.0,-10.0,10.0);
//int yaw_mapped = delta_yaw;
  
  ESCout_1 = input_THROTTLE + roll_mapped - pitch_mapped - yaw_mapped;
  ESCout_2 = input_THROTTLE - roll_mapped + pitch_mapped - yaw_mapped;
  ESCout_3 = input_THROTTLE - roll_mapped - pitch_mapped + yaw_mapped;
  ESCout_4 = input_THROTTLE + roll_mapped + pitch_mapped + yaw_mapped;
  
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
//    Serial.print("Yaw mapped: ");Serial.println(yaw_mapped);
}
