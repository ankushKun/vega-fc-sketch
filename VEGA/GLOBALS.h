
///// CONFIGS /////
// Comment a line to disable

#define DEBUG
//#define CALIBRATE_RECIEVER
//#define ENABLE_WIFI
#define CALIBRATE_ESC
#define CALIBRATE_MPU

#ifdef DEBUG
  #define DEBUG_BOOL true
#else
  #define DEBUG_BOOL false
#endif
#define LOG if(DEBUG_BOOL)

///// VARS /////
#define PUSH_BUTTON_1 18
bool has_display = true;
bool armed = false;
bool crashed = false;
bool killed = false;

///// WIFI /////
char* AP="VEGA_DRONE";
char* PASS="BlackFalcon69";


///// ESC VARS /////
#define ESC1 0
#define ESC2 1
#define ESC3 2
#define ESC4 3
int minThrottle = 0, maxThrottle = 128;
int ESCout_1 ,ESCout_2 ,ESCout_3 ,ESCout_4;
int esc1mapped, esc2mapped, esc3mapped, esc4mapped;
int input_PITCH = 0;
int input_ROLL = 0;
int input_YAW = 0;
int input_THROTTLE=0;
int state1,state2,state3,state4;

///// GYRO VARS /////
//Declaring some global variables
int16_t gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, temperature, acc_total_vector;
float angle_pitch, angle_roll, angle_yaw;
float delta_yaw;
int roll_mapped, pitch_mapped, yaw_mapped;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;
float elapsedTime;
long Time = micros(), timePrev, time2;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
double offsetX,offsetY,offsetZ;
double rollOffset=0.0, pitchOffset=0.0, yawOffset=0.0;

///// PID VARS /////
// Roll PID
float roll_error = 0;
float roll_integral = 0;
float roll_derivative = 0;
float roll_previous_error = 0;

// Pitch PID
float pitch_error = 0;
float pitch_integral = 0;
float pitch_derivative = 0;
float pitch_previous_error = 0;

// Roll and Pitch PID params
float roll_Kp = 1;
float roll_Ki = 0.000;
float roll_Kd = 0.000;

float pitch_Kp = 1;
float pitch_Ki = 0.000;
float pitch_Kd = 0.000;

// Yaw PID
float yaw_error = 0;
float yaw_integral = 0;
float yaw_derivative = 0;
float yaw_previous_error = 0;
float yaw_Kp = 1;
float yaw_Ki = 0.000;
float yaw_Kd = 0.000;

///// REMOTE CALIBRATION /////
int throttleRaw, rollRaw, pitchRaw, yawRaw, killRaw, modeRaw, btnRaw;
int THROTTLE_MIN = 1100, THROTTLE_MAX = 2000;
int ROLL_MIN = 1100, ROLL_MAX = 2000;
int PITCH_MIN = 1100, PITCH_MAX = 2000;
int YAW_MIN = 1100, YAW_MAX = 2000;
