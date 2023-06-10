
///// CONFIGS /////
// Comment a line to disable
#define DEBUG
#define CALIBRATE_ESC
#define CALIBRATE_MPU

///// VARS /////
#define PUSH_BUTTON_1 18
bool crashed = false;

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
float roll_Kp = 0.1;    // Proportional gain
float roll_Ki = 0.01;   // Integral gain
float roll_Kd = 0.05;   // Derivative gain

// Pitch PID
float pitch_error = 0;
float pitch_integral = 0;
float pitch_derivative = 0;
float pitch_previous_error = 0;
float pitch_Kp = 0.1;   // Proportional gain
float pitch_Ki = 0.01;  // Integral gain
float pitch_Kd = 0.05;  // Derivative gain

// Yaw PID
float yaw_error = 0;
float yaw_integral = 0;
float yaw_derivative = 0;
float yaw_previous_error = 0;
float yaw_Kp = 0.1;     // Proportional gain
float yaw_Ki = 0.01;    // Integral gain
float yaw_Kd = 0.05;    // Derivative gain
