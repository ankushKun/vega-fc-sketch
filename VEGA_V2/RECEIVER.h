
int mid(int min_, int max_){
  return ((min_+max_)/2);
}

void SetupRECEIVER(){
  oledPrint("SETUP\nRECEIVER",2,true,true,true);
  Serial.print("SETTING UP RECEIVER... ");
  pinMode(CH_THR, INPUT);
  pinMode(CH_ROL, INPUT);
  pinMode(CH_PIT, INPUT);
  pinMode(CH_YAW, INPUT);
  pinMode(CH_KIL, INPUT);
  pinMode(CH_MOD, INPUT);
  pinMode(CH_BTN, INPUT);
  Serial.println("DONE");
  oledPrint("DONE",2,true,true,true);
}

void LoopRECEIVER(){
  throttleRaw = pulseIn(CH_THR, HIGH);
  delay(1);
  rollRaw = pulseIn(CH_ROL, HIGH);
  delay(1);
  pitchRaw = pulseIn(CH_PIT, HIGH);
  delay(1);
  yawRaw = pulseIn(CH_YAW, HIGH);
  delay(1);
  killRaw = pulseIn(CH_KIL, HIGH);
  delay(1);
  modeRaw = pulseIn(CH_MOD, HIGH);
  delay(1);
  btnRaw = pulseIn(CH_BTN, HIGH);

  if(!killed && killRaw > 1550) killed = true;

  if(modeRaw < 1500)armed = false;
  else if(modeRaw>=1500)armed = true; 

  input_THROTTLE = map(throttleRaw, sigMinRaw, sigMaxRaw, sigMin, sigMax);
  input_ROLL = map(rollRaw, sigMinRaw, sigMaxRaw, -40, 40);
  input_PITCH = map(pitchRaw, sigMinRaw, sigMaxRaw, -40, 40);
  input_YAW = map(yawRaw, sigMinRaw, sigMaxRaw, -40, 40);

//  input_THROTTLE = throttleRaw;
//  input_ROLL = rollRaw;
//  input_PITCH = pitchRaw;
//  input_YAW = yawRaw;
}

boolean btnHigh(){LoopRECEIVER();return (boolean)(btnRaw>1550);}
boolean btnLow(){LoopRECEIVER();return (boolean)(btnRaw<=1550);}
