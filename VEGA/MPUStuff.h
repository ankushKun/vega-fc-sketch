#include <Wire.h>
#include <TinyMPU6050.h>

TwoWire Wire(1);
MPU6050 mpu (Wire);

void SetupMPU(){
  mpu.Initialize();
  Serial.println("-> Calibrating MPU...");
  mpu.Calibrate();
  Serial.println("-> Calibration complete!");
//  Serial.println("-> Offsets:");
//  Serial.print("-> GyroX Offset = ");
//  Serial.println(mpu.GetGyroXOffset());
//  Serial.print("-> GyroY Offset = ");
//  Serial.println(mpu.GetGyroYOffset());
//  Serial.print("-> GyroZ Offset = ");
//  Serial.println(mpu.GetGyroZOffset());
  Time = micros(); 
}

void ReadFromMPU() {                                          
  timePrev = Time;
  Time = micros();
  elapsedTime = (float)(Time - timePrev) / (float)1000000;

  mpu.Execute();
  angle_roll = mpu.GetAngY();
  angle_pitch = mpu.GetAngX();
  angle_yaw = mpu.GetAngZ();

  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;
  
  roll_desired_angle = 3*((float)input_ROLL/(float)10 - (float)5);
  pitch_desired_angle = 3*((float)input_PITCH/(float)10 - (float)5);
  //yaw_desired_angle =0;

  roll_error =  angle_roll_output - roll_desired_angle;
  pitch_error = angle_pitch_output - pitch_desired_angle;  
  yaw_error = angle_yaw - yaw_desired_angle; 

  roll_pid_p = twoX_kp*roll_error;
  pitch_pid_p = twoX_kp*pitch_error;
  yaw_pid_p = yaw_kp*yaw_error;

  if(-3 < roll_error <3){roll_pid_i = roll_pid_i+(twoX_ki*roll_error);}
  if(-3 < pitch_error <3){pitch_pid_i = pitch_pid_i+(twoX_ki*pitch_error);}
  if(-3 < yaw_error <3){yaw_pid_i = yaw_pid_i+(yaw_ki*yaw_error);}

 
  roll_pid_d = twoX_kd*((roll_error - roll_previous_error)/elapsedTime);
  pitch_pid_d = twoX_kd*((pitch_error - pitch_previous_error)/elapsedTime);
  roll_PID = roll_pid_p + roll_pid_i + roll_pid_d;
  pitch_PID = pitch_pid_p + pitch_pid_i + pitch_pid_d;
  yaw_PID = yaw_pid_p + yaw_pid_i;

  if(roll_PID < -400){roll_PID=-400;}
  else if(roll_PID > 400) {roll_PID=400;}
  if(pitch_PID < -400){pitch_PID=-400;}
  else if(pitch_PID > 400) {pitch_PID=400;}
  if(yaw_PID < -400){yaw_PID=-400;}
  else if(yaw_PID > 400) {yaw_PID=400;}
  
  ESCout_1 = input_THROTTLE - roll_PID - pitch_PID - yaw_PID;
  ESCout_2 = input_THROTTLE + roll_PID - pitch_PID + yaw_PID;
  ESCout_3 = input_THROTTLE + roll_PID + pitch_PID - yaw_PID;
  ESCout_4 = input_THROTTLE - roll_PID + pitch_PID + yaw_PID;
  
  if(ESCout_1>2000) ESCout_1=2000;
  else if(ESCout_1<1100) ESCout_1=1100;
  if(ESCout_2>2000) ESCout_2=2000;
  else if(ESCout_2<1100) ESCout_2=1100;
  if(ESCout_3>2000) ESCout_3=2000;
  else if(ESCout_3<1100) ESCout_3=1100;
  if(ESCout_4>2000) ESCout_4=2000;
  else if(ESCout_4<1100) ESCout_4=1100;

  roll_previous_error = roll_error;
  pitch_previous_error = pitch_error;

  LOG {
    Serial.print(">");
    Serial.print(angle_roll);Serial.print(" R ");
    Serial.print(angle_pitch);Serial.print(" P ");
    Serial.print(angle_yaw);Serial.println(" Y ");
  }
}
