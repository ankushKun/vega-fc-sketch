//#include <Wire.h>
//TwoWire Wire(0);

#define CALIBRATE_IMU
#define CALIBRATE_ESC
#define ENABLE_WIFI

//// VARIABLES
bool killed=false;
bool crashed=false;
bool armed=false;

///// IMU
float AngleRoll=0, AnglePitch=0, AngleYaw=0;
float AngleRollOffset=0, AnglePitchOffset=0, AngleYawOffset=0;
uint32_t LoopTimer = micros();

///// RECEIVER
#define CH_ROL 0  // roll        -> channel 1
#define CH_PIT 1  // pitch       -> channel 2
#define CH_THR 2  // throttle    -> channel 3
#define CH_YAW 3  // Yaw         -> channel 4
#define CH_KIL 11 // Kill switch -> channel 5
#define CH_BTN 12 // Button calibration ->  6
#define CH_MOD 13 // Mode        -> channel 7
int sigMinRaw=1100, sigMaxRaw=2000;
int sigMin=0, sigMax=128;
int throttleRaw, rollRaw, pitchRaw, yawRaw, killRaw, btnRaw, modeRaw;
int throttleMin=sigMinRaw, rollMin=sigMinRaw, pitchMin=sigMinRaw, yawMin=sigMinRaw, killMin=sigMinRaw, btnMin=sigMinRaw, modeMin=sigMinRaw;
int throttleMax=sigMaxRaw, rollMax=sigMaxRaw, pitchMax=sigMaxRaw, yawMax=sigMaxRaw, killMax=sigMaxRaw, btnMax=sigMaxRaw, modeMax=sigMaxRaw;

///// MOTOR
#define ESC1 0
#define ESC2 1
#define ESC3 2
#define ESC4 3
int input_PITCH=0, input_ROLL=0, input_YAW=0, input_THROTTLE=0;
int ESCout_1=0, ESCout_2=0, ESCout_3=0, ESCout_4=0;

///// PID VARS
float roll_Kp = 1;
float roll_Ki = 0.000;
float roll_Kd = 0.000;

float pitch_Kp = 1;
float pitch_Ki = 0.000;
float pitch_Kd = 0.000;

float yaw_Kp = 1;
float yaw_Ki = 0.000;
float yaw_Kd = 0.000;


float roll_error = 0;
float roll_integral = 0;
float roll_derivative = 0;
float roll_previous_error = 0;


float pitch_error = 0;
float pitch_integral = 0;
float pitch_derivative = 0;
float pitch_previous_error = 0;


float yaw_error = 0;
float yaw_integral = 0;
float yaw_derivative = 0;
float yaw_previous_error = 0;

float rollAdjusted=0.0, pitchAdjusted=0.0, yawAdjusted=0.0;

///// OLED
uint32_t oledTimer = micros();
uint32_t lastDisplay = micros();
