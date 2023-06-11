
///// CONFIGS /////
// Comment a line to disable
#define DEBUG
#define CALIBRATE_ESC
#define CALIBRATE_MPU
//#define CALIBRATE_RECIEVER
//#define ENABLE_WIFI

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
int input_THROTTLE=55;
int state1,state2,state3,state4;

///// GYRO VARS /////
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
float XY_Kp = 0.6;
float XY_Ki = 0.000;
float XY_Kd = 0.000;

// Yaw PID
float yaw_error = 0;
float yaw_integral = 0;
float yaw_derivative = 0;
float yaw_previous_error = 0;
float yaw_Kp = 0.0;
float yaw_Ki = 0.000;
float yaw_Kd = 0.000;

///// REMOTE CALIBRATION /////
int throttleRaw, rollRaw, pitchRaw, yawRaw, killRaw, modeRaw, btnRaw;
int THROTTLE_MIN = 1100, THROTTLE_MAX = 2000;
int ROLL_MIN = 1100, ROLL_MAX = 2000;
int PITCH_MIN = 1100, PITCH_MAX = 2000;
int YAW_MIN = 1100, YAW_MAX = 2000;
