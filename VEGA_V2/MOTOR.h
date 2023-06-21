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
    oledPrint("UNARM\nDROME",2,true,true,true);
    Serial.println("UNARM DRONE TO BEFORE ESC CALIBRATION");
    while(armed){}
  }
  if(crashed || killed)return;
  boolean loopThis;
  #ifdef CALIBRATE_ESC
    oledPrint("LOWER\nSWITCH",2,true,true,true);
    Serial.println("FLIP SWITCH TO LOW");
//    for(boolean loopThis = btnHigh();loopThis;loopThis = btnHigh());
    loopThis = btnHigh();
    while(loopThis){loopThis = btnHigh();} // wait till user goes from high to low
    oledPrint("REMOVE POWER\nFLIP SWITCH",1,true,true,true);
    Serial.println("STARTING ESC CALIBRATION...\tREMOVE POWER FROM ESCs\t Flip Switch");
    loopThis = btnLow();
    while(loopThis){loopThis = btnLow();} // wait till user goes from low to high
    Serial.println("GIVING FULL THROTTLE");
    oledPrint("GIVING\nTHROTTLE",2,true,true,true);
    delay(1000);
  #else
    Serial.println("CALIBRATE ESC WAS CALLED EVEN WHEN CALIBRATE_ESC IS FALSE");
    return;
  #endif

  loopThis = false;
  bool displayed = false;
  while(true){
    if(!calibrated){
      esc1.write(sigMax);
      esc2.write(sigMax);
      esc3.write(sigMax);
      esc4.write(sigMax);
      if(!displayed){
       oledPrint("GIVE POWER\nFLIP SWITCH",2,true,true,true);
       displayed = true; 
      }
      Serial.println("GIVE POWER TO ESCs NOW \tFULL THROTTLE\t");
      if(btnLow()){
        calibrated = true;
        Serial.println("BTN FLIP DETECTED \tLOWERING THROTTLE");
        loopThis = btnLow();
        while(loopThis){
          if(isLow){
            esc1.write(sigMin);
            esc2.write(sigMin);
            esc3.write(sigMin);
            esc4.write(sigMin);
            Serial.println("NO THROTTLE\t RELEASE BUTTON");
            loopThis = btnLow();
          }else{
            for(int i=sigMax;i>20;i--){
              Serial.print("CURRENT THRORRLE: ");Serial.println(i);
              if(i%10==0)oledPrint((String)i,2,true,true,true);
              esc1.write(i);
              esc2.write(i);
              esc3.write(i);
              esc4.write(i);
              if(i==21){
                isLow=true;
                oledPrint("FLIP\nSWITCH",2,true,true,true);
              }
              delay(10);
            }
          }
          loopThis = btnLow();
        }
        Serial.print("WAITING FOR ESCs TO ACTIVATE ");
        oledPrint("ACTIVATING\nESCs",2,true,true,true);
        for(int i=0;i<128;i++){
          if(i%10==0){Serial.print(".");}
          esc1.write(20);
          esc2.write(20);
          esc3.write(20);
          esc4.write(20);
          delay(1);
        }
        oledPrint("CALIBRATION\nDONE",2,true,true,true);
        Serial.println("CALIBRATION DONE!");
        delay(1000); 
        break;
      }
    }
  }
}

void SetupMOTOR(){
  oledPrint("SETUP\nMOTORS",2,true,true,true);
  Serial.print("SETTING UP ESC AND MOTORS... ");
  esc1.attach(ESC1);
  esc2.attach(ESC2);
  esc3.attach(ESC3);
  esc4.attach(ESC4);
  Serial.println("DONE");
  oledPrint("DONE",2,true,true,true);
#ifdef CALIBRATE_ESC
  CalibrateESC();
#endif
}

void LoopMOTOR(){
  ESCout_1 = input_THROTTLE - rollAdjusted - pitchAdjusted - yawAdjusted;
  ESCout_2 = input_THROTTLE + rollAdjusted + pitchAdjusted - yawAdjusted;
  ESCout_3 = input_THROTTLE + rollAdjusted - pitchAdjusted + yawAdjusted;
  ESCout_4 = input_THROTTLE - rollAdjusted + pitchAdjusted + yawAdjusted;

  if(ESCout_1<input_THROTTLE)ESCout_1=input_THROTTLE;
  if(ESCout_2<input_THROTTLE)ESCout_2=input_THROTTLE;
  if(ESCout_3<input_THROTTLE)ESCout_3=input_THROTTLE;
  if(ESCout_4<input_THROTTLE)ESCout_4=input_THROTTLE;
  
  ESCout_1 = constrain(ESCout_1, sigMin, sigMax);
  ESCout_2 = constrain(ESCout_2, sigMin, sigMax);
  ESCout_3 = constrain(ESCout_3, sigMin, sigMax);
  ESCout_4 = constrain(ESCout_4, sigMin, sigMax);

  if(!armed){
    ESCout_1 = 0;
    ESCout_2 = 0;
    ESCout_3 = 0;
    ESCout_4 = 0;
    oledPrint("UNARMED",2,true,true,false);
  }
  if(killed){
    ESCout_1 = 0;
    ESCout_2 = 0;
    ESCout_3 = 0;
    ESCout_4 = 0;
    oledPrint("KILLED",2,true,true,false);
  }

  const int x = 20;
  const int y = 2;

  if(armed && !killed){
    display.clearDisplay();
    display.setCursor(x,y);
    display.print(ESCout_3);
    display.setCursor(x+70,y);
    display.print(ESCout_1);
    display.setCursor(x,y+15);
    display.print(ESCout_2);
    display.setCursor(x+70,y+15);
    display.print(ESCout_4);
  }
  
  esc1.write(ESCout_1);
  esc2.write(ESCout_2);
  esc3.write(ESCout_3);
  esc4.write(ESCout_4);
}
