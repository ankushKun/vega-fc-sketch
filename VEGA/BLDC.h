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

bool calibrated = false;
bool isLow = false;

void CalibrateESC(){
  if(armed){
    writeText("UNARM DRONE TO CALIBRATE ESC");
    Serial.println("UNARM DRONE TO BEFORE ESC CALIBRATION");
    while(armed){}
  }
  if(crashed || killed)return;
  boolean loopThis;
  #ifdef CALIBRATE_ESC
    writeText("FLIP SWITCH TO LOW");
    Serial.println("FLIP SWITCH TO LOW");
//    for(boolean loopThis = btnHigh();loopThis;loopThis = btnHigh());
    loopThis = btnHigh();
    while(loopThis){loopThis = btnHigh();} // wait till user goes from high to low
    writeText("ESC CALIBRAION\nREMOVE POWER FROM ESC\nFLIP CALIBRATION SWITCH");
    Serial.println("STARTING ESC CALIBRATION...\tREMOVE POWER FROM ESCs\t Flip Switch");
    loopThis = btnLow();
    while(loopThis){loopThis = btnLow();} // wait till user goes from low to high
    Serial.println("GIVING FULL THROTTLE");
    writeText("GIVING FULL THROTTLE");
    delay(2000);
  #else
    Serial.println("CALIBRATE ESC WAS CALLED EVEN WHEN CALIBRATE_ESC IS FALSE");
    return;
  #endif

  bool printed = false;
  loopThis = false;
  while(true){
    if(!calibrated){
      esc1.write(128);
      esc2.write(128);
      esc3.write(128);
      esc4.write(128);
      if(!printed){
        writeText("GIVE POWER TO ESC\nFLIP SWITCH TO LOW");
        printed = true;
      }
      Serial.print("GIVE POWER TO ESCs NOW \tFULL THROTTLE\t");
      if(btnLow()){
        calibrated = true;
        Serial.println("BTN1 PUSH DETECTED \tLOWERING THROTTLE");
        loopThis = btnLow();
        while(loopThis){
          if(isLow){
            esc1.write(20);
            esc2.write(20);
            esc3.write(20);
            esc4.write(20);
            Serial.println("NO THROTTLE\t RELEASE BUTTON");
            loopThis = btnLow();
          }else{
            for(int i=128;i>20;i--){
              Serial.print("CURRENT THRORRLE: ");Serial.println(i);
              if(i%4==0)writeText((String)i);
              esc1.write(i);
              esc2.write(i);
              esc3.write(i);
              esc4.write(i);
              if(i==21){
                isLow=true;
                writeText("FLIP SWITCH");
              }
              delay(5);
            }
          }
          loopThis = btnLow();
        }
        Serial.print("WAITING FOR ESCs TO ACTIVATE ");
        writeText("ACTIVATING ESCs");
        for(int i=0;i<128;i++){
          if(i%100==0){Serial.print(i/100);Serial.print("... ");}
          esc1.write(20);
          esc2.write(20);
          esc3.write(20);
          esc4.write(20);
          delay(2);
        }
        writeText("CALIBRATION COMPLETE");
        Serial.println("CALIBRATION DONE!");
        delay(3000);
        
        break;
      }
    }
  }
}

void DetachESC(){
  esc1.detach();
  esc2.detach();
  esc3.detach();
  esc4.detach();
  Serial.println("ESCs Detached");
  writeText("   ESCs\nDETACHED");
}

void AttachESC(){
  esc1.attach(ESC1);
  esc2.attach(ESC2);
  esc3.attach(ESC3);
  esc4.attach(ESC4);
  Serial.println("ESCs Attached");
  writeText("   ESCs\nATTACHED");
}

void SetupESC(){
  AttachESC();
  delay(1000);
#ifdef CALIBRATE_ESC
  CalibrateESC();
#endif
}

void WriteESC(){
  if(killed || !armed || crashed){
    ESCout_1 = 0;
    ESCout_2 = 0;
    ESCout_3 = 0;
    ESCout_4 = 0;
    DetachESC();
    delay(333);
    if(killed){
      writeText("KILLED");
      Serial.println("KILLED");
    } else if(!armed){
      writeText("UNARMED");
      Serial.println("UNARMED");
    } else if(crashed){
      writeText("CRASHED");
      Serial.println("CRASHED");
    }
    delay(333);
  }
  esc1.write(ESCout_1);
  esc2.write(ESCout_2);
  esc3.write(ESCout_3);
  esc4.write(ESCout_4);
}
