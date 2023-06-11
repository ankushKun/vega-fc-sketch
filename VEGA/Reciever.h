#include <pwm.h>

#define CH_ROL 0
#define CH_PIT 1
#define CH_THR 2
#define CH_YAW 3
#define CH_KIL 4

//void CalibrateReciever(){
//  Serial.println("CALIBRATING RECIEVER");
//  while(1){
//    if(digitalRead(PUSH_BUTTON_1)==LOW)break;
//    
//    int throttle = pulseIn(CH_THR, HIGH, 1000);
//    int roll = pulseIn(CH_ROL, HIGH, 1000);
//    int pitch = pulseIn(CH_PIT, HIGH, 1000);
//    int yaw = pulseIn(CH_YAW, HIGH, 1000);
////    int kill = pulseIn(CH_KIL, HIGH);
//
//    if(throttle < THROTTLE_MIN)THROTTLE_MIN = throttle;
//    if(throttle > THROTTLE_MAX)THROTTLE_MAX = throttle;
//    Serial.print("THROTTLE: ");Serial.print(throttle);Serial.print("\t");Serial.print(THROTTLE_MIN);Serial.print("-");Serial.println(THROTTLE_MAX);
//  
//    if(roll < ROLL_MIN)ROLL_MIN = roll;
//    if(roll > ROLL_MAX)ROLL_MAX = roll;
//    Serial.print("ROLL: ");Serial.print(roll);Serial.print("\t");Serial.print(ROLL_MIN);Serial.print("-");Serial.println(ROLL_MAX);
//
//    if(pitch < PITCH_MIN)PITCH_MIN = pitch;
//    if(pitch > PITCH_MAX)PITCH_MAX = pitch;
//    Serial.print("PITCH: ");Serial.print(pitch);Serial.print("\t");Serial.print(PITCH_MIN);Serial.print("-");Serial.println(PITCH_MAX);
//
//    if(yaw < YAW_MIN)YAW_MIN = yaw;
//    if(yaw > YAW_MAX)YAW_MAX = yaw;
//    Serial.print("YAW: ");Serial.print(yaw);Serial.print("\t");Serial.print(YAW_MIN);Serial.print("-");Serial.println(YAW_MAX);
//    delay(10);
//  }
//  Serial.println("RECIEVER CALIBRATED");
//}

void SetupReciever(){
  pinMode(CH_THR, INPUT);
  pinMode(CH_ROL, INPUT);
  pinMode(CH_PIT, INPUT);
  pinMode(CH_YAW, INPUT);
  pinMode(CH_KIL, INPUT);
  Serial.println("RECIEVER SETUP");
//  #ifdef CALIBRATE_TRANSMITTER
//  CalibrateReciever();
//  #endif
}

void ReadReciever(){
//   Serial.println("reading");
  throttleRaw = pulseIn(CH_THR, HIGH, 1000);
  Serial.print("THROTTLE: ");Serial.print(throttleRaw);
  rollRaw = pulseIn(CH_ROL, HIGH, 1000);
  Serial.print("\tROLL: ");Serial.print(rollRaw );
  pitchRaw = pulseIn(CH_PIT, HIGH, 1000);
  Serial.print("\tPITCH: ");Serial.print(pitchRaw);
  yawRaw = pulseIn(CH_YAW, HIGH, 1000);
  Serial.print("\tYAW: ");Serial.println(yawRaw);
//  int kill = pulseIn(CH_KIL, HIGH, 1000);
  
//  Serial.print("KILL: ");Serial.println(kill);
//  if(!killed && kill <=500) killed = true;

  input_THROTTLE = map(throttleRaw, 1100, 2000, minThrottle, maxThrottle);
  input_ROLL = map(rollRaw, 1100, 2000, -90, 90);
  input_PITCH = map(pitchRaw, 1100, 2000, 90, -90);
  
}
