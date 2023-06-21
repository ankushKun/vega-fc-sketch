#include "MPU9250.h"
MPU9250 mpu;

void print_calibration() {
    Serial.println("< calibration parameters >");
    Serial.println("accel bias [g]: ");
    Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.println();
    Serial.println("gyro bias [deg/s]: ");
    Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.println();
    Serial.println("mag bias [mG]: ");
    Serial.print(mpu.getMagBiasX());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasY());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasZ());
    Serial.println();
    Serial.println("mag scale []: ");
    Serial.print(mpu.getMagScaleX());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleY());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleZ());
    Serial.println();
}

void SetupIMU(){
  delay(2000);
  if (!mpu.setup(0x68)) {
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            oledPrint("IMU NOT\nFOUND",2,true,true,true);
            delay(5000);
        }
    }
  delay(3000);
  mpu.verbose(true);
//  mpu.setMagneticDeclination(1.73);
  #ifdef CALIBRATE_IMU
  Serial.println("Accel Gyro calibration will start in 5sec.");
  Serial.println("Please leave the device still on the flat plane.");
  oledPrint("PLACE DRONE ON\nFLAT SURFACE",1,true,true,true);
  delay(2000);
  oledPrint("CALIBRATING GYRO",1,true,true,true);
  mpu.calibrateAccelGyro();
  oledPrint("DONE",1,true,true,true);
  delay(1000);
  
  Serial.println("Mag calibration will start in 5sec.");
  Serial.println("Please Wave device in a figure eight until done.");
  delay(2000);
  oledPrint("CALIBRATING MAGNETOMETER\nMOVE IN 8 SHAPE",1,true,true,true);
  mpu.calibrateMag();
  print_calibration();
  delay(1000);
  #endif
  Serial.println("PLACE DRONE ON A FLAT SURFACE");
  oledPrint("PLACE DRONE ON FLAT SURFACE",1,true,true,true);
  delay(7000);
  float r=0.0,p=0.0,y=0.0;
  for(int i=0;i<1001;i++){
    mpu.update();
    if(i>500){
      r+=mpu.getPitch();
      p+=mpu.getRoll();
      y+=mpu.getYaw();
    }
    Serial.print("Roll ");
    Serial.print(mpu.getRoll());
    Serial.print(" Pitch ");
    Serial.print(mpu.getPitch());
    Serial.print(" Yaw ");
    Serial.println(mpu.getYaw());
    if(i%100==0){
      oledPrint((String)((i/100)+1),1,true,false,false);
      oledPrint(" ",1,false,false,true);
    }
    delay(10);
  }
  AngleRollOffset = r/500.0;
  AnglePitchOffset = p/500.0;
  AngleYawOffset = y/500.0;
  Serial.print("RollOffset: ");Serial.println(AngleRollOffset);
  Serial.print("PitchOffset: ");Serial.println(AnglePitchOffset);
  Serial.print("YawOffset: ");Serial.println(AngleYawOffset);
  
  oledPrint("DONE",1,true,true,true);
  delay(1000);
//  mpu.verbose(false);
}

void LoopIMU(){
  mpu.update();
// SWAP ROLL AND PITCH
  AngleYaw = mpu.getYaw();
  AngleYaw -= AngleYawOffset;
//AngleYaw = 0;
  AnglePitch = mpu.getRoll();
  AnglePitch -= AnglePitchOffset;
  AngleRoll = mpu.getPitch();
  AngleRoll -= AngleRollOffset;
}
