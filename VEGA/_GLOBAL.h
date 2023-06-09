#define DEBUG 1
#define CALIBRATE_ESC false
#define NO_YAW true

#define TRUE 1
#define FALSE 0
#define LOG if(DEBUG)

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
int input_YAW;
int input_THROTTLE=35;
int state1,state2,state3,state4;

///// GYRO VARS /////
int16_t gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, temperature, acc_total_vector;
float angle_pitch, angle_roll, angle_yaw;
boolean set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;
float elapsedTime;
long Time = micros(), timePrev, time2;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
double offsetX,offsetY,offsetZ;


///// PID VARS /////
float pitch_PID,roll_PID,yaw_PID;
float roll_error, roll_previous_error, pitch_error, pitch_previous_error, yaw_error;
float roll_pid_p, roll_pid_d, roll_pid_i, pitch_pid_p, pitch_pid_i, pitch_pid_d, yaw_pid_p, yaw_pid_i;
float roll_desired_angle, pitch_desired_angle, yaw_desired_angle; 
double twoX_kp=5;      
double twoX_ki=0.003;
double twoX_kd=2;     
double yaw_kp=3;    
double yaw_ki=0.002;
