#include <Servo.h>

/*  ATTACH TO PWM PINS
 *  
 *     ESC3     ESC1
 *      2        0
 *  
 *     ESC2     ESC4
 *      1        3
 *      
 *   <STANDARD DRONE
 *   MOTOR ARRANGEMENT>
 */

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

void SetupMOTOR(){
  Serial.print("SETTING UP ESC AND MOTORS... ");
  esc1.attach(ESC1);
  esc2.attach(ESC2);
  esc3.attach(ESC3);
  esc4.attach(ESC4);
  Serial.println("DONE");
}

void LoopMOTOR(){
//  ESCout_1 = input_THROTTLE - input_ROLL - input_PITCH + input_YAW;
//  ESCout_2 = input_THROTTLE + input_ROLL + input_PITCH + input_YAW;
//  ESCout_3 = input_THROTTLE + input_ROLL - input_PITCH - input_YAW;
//  ESCout_4 = input_THROTTLE - input_ROLL + input_PITCH - input_YAW;

  
  ESCout_1 = input_THROTTLE + rollAdjusted - pitchAdjusted + yawAdjusted;
  ESCout_2 = input_THROTTLE - rollAdjusted + pitchAdjusted + yawAdjusted;
  ESCout_3 = input_THROTTLE - rollAdjusted - pitchAdjusted - yawAdjusted;
  ESCout_4 = input_THROTTLE + rollAdjusted + pitchAdjusted - yawAdjusted;


  ESCout_1 = constrain(ESCout_1, sigMin, sigMax);
  ESCout_2 = constrain(ESCout_2, sigMin, sigMax);
  ESCout_3 = constrain(ESCout_3, sigMin, sigMax);
  ESCout_4 = constrain(ESCout_4, sigMin, sigMax);
  
  esc1.write(ESCout_1);
  esc2.write(ESCout_2);
  esc3.write(ESCout_3);
  esc4.write(ESCout_4);
}
