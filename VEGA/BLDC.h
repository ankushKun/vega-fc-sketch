#include <Servo.h>

/*  FOR PWM PINS
 *  
 *  ESC3     ESC1
 *   2        0
 *  
 *  ESC2     ESC4
 *   1        3
 *  
 */

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

bool calibrated = false;
bool isLow = false;

void CalibrateESC(){
  if(!CALIBRATE_ESC){
    Serial.println("CALIBRATE ESC WAS CALLED EVEN WHEN CALIBRATE_ESC IS FALSE");
    return;
  };
  Serial.println("->STARTING ESC CALIBRATION...\tREMOVE POWER FROM ESCs");
  delay(3000);
  while(true){
    if(!calibrated){
      Serial.print("-> GIVE POWER TO ESCs NOW \tFULL THROTTLE\t");
      esc1.write(128);
      esc2.write(128);
      esc3.write(128);
      esc4.write(128);
      if(digitalRead(PUSH_BUTTON_1)==LOW){
        calibrated = true;
        Serial.println("-> BTN1 PUSH DETECTED \tLOWERING THROTTLE");
        while(digitalRead(PUSH_BUTTON_1)==LOW){
          if(isLow){
            esc1.write(0);
            esc2.write(0);
            esc3.write(0);
            esc4.write(0);
            delay(10);
            Serial.println("NO THROTTLE\t RELEASE BUTTON");
          }else{
            for(int i=128;i>0;i--){
              Serial.print("CURRENT THRORRLE: ");Serial.println(i);
              esc1.write(i);
              esc2.write(i);
              esc3.write(i);
              esc4.write(i);
              if(i=1)isLow=true;
              delay(10);
            }
          }
        }
        Serial.print("WAITING FOR ESCs TO ACTIVATE ");
        for(int i=0;i<500;i++){
          if(i%100==0){Serial.print(i/100);Serial.print("... ");}
          esc1.write(0);
          esc2.write(0);
          esc3.write(0);
          esc4.write(0);
          delay(10);
        }
        Serial.println("-> CALIBRATION DONE!");
        break;
      }else{
        Serial.println("PRESS AND HOLD BUTTON 1");
      }
    }
    delay(10);
  }
}

void SetupESC(){
  esc1.attach(ESC1);
  esc2.attach(ESC2);
  esc3.attach(ESC3);
  esc4.attach(ESC4);
  Serial.println("-> ESCs Attached");
}

void Oscillate(int maxim){
  for(int i=0;i<maxim;i++){
    esc1.write(i);
    esc2.write(i);
    esc3.write(i);
    esc4.write(i);
    Serial.print("-> ");
    Serial.println(i);
    delay(100);
  }
  for(int i=maxim;i>0;i--){
    esc1.write(i);
    esc2.write(i);
    esc3.write(i);
    esc4.write(i);
    Serial.print("-> ");
    Serial.println(i);
    delay(100);
  }
}

void WriteESC(){
  if(crashed){
      ESCout_1 = 0;
      ESCout_2 = 0;
      ESCout_3 = 0;
      ESCout_4 = 0;
      Serial.println("CRASHED");
  }
  
      esc1.write(ESCout_1);
      esc2.write(ESCout_2);
      esc3.write(ESCout_3);
      esc4.write(ESCout_4);

      Serial.print("ESC3: ");
      Serial.print(ESCout_3);
      Serial.print("\tESC1: ");
      Serial.println(ESCout_1);
      Serial.print("ESC2: ");
      Serial.print(ESCout_2);
      Serial.print("\tESC4: ");
      Serial.println(ESCout_4);
}
