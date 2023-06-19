

int mid(int min_, int max_){
  return ((min_+max_)/2);
}

void SetupRECEIVER(){
  Serial.print("SETTING UP RECEIVER... ");
  pinMode(CH_THR, INPUT);
  pinMode(CH_ROL, INPUT);
  pinMode(CH_PIT, INPUT);
  pinMode(CH_YAW, INPUT);
  pinMode(CH_KIL, INPUT);
  Serial.println("DONE");
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

//  throttleMin = min(throttleMin, throttleRaw);
//  throttleMax = max(throttleMax, throttleRaw);
//  rollMin = min(rollMin, rollRaw);
//  rollMax = max(rollMax, rollRaw);
//  pitchMin = min(pitchMin, pitchRaw);
//  pitchMax = max(pitchMax, pitchRaw);
//  yawMin = min(yawMin, yawRaw);
//  yawMax = max(yawMax, yawRaw);
//  killMin = min(killMin, killRaw);
//  killMax = max(killMax, killRaw);
//  modeMin = min(modeMin, modeRaw);
//  modeMax = max(modeMax, modeRaw);
//  btnMin = min(btnMin, btnRaw);
//  btnMax = max(btnMax, btnRaw);

  if(!killed && killRaw > mid(killMin, killMax)) killed = true;

  if(modeRaw <= (mid(modeMin, modeMax))-100){
    armed = false;
  }else if(modeRaw>(mid(modeMin, modeMax))+100){
    armed = true;
  }

//  input_THROTTLE = map(throttleRaw, throttleMin, throttleMax, sigMin, sigMax);
//  input_ROLL = map(rollRaw, rollMin, rollMax, -40, 40);
//  input_PITCH = map(pitchRaw, pitchMin, pitchMax, -40, 40);
//  input_YAW = map(yawRaw, yawMin, yawMax, -40, 40);

    input_THROTTLE = map(throttleRaw, sigMinRaw, sigMaxRaw, sigMin, sigMax);
  input_ROLL = map(rollRaw, sigMinRaw, sigMaxRaw, -40, 40);
  input_PITCH = map(pitchRaw, sigMinRaw, sigMaxRaw, -40, 40);
  input_YAW = map(yawRaw, sigMinRaw, sigMaxRaw, -40, 40);

//  input_THROTTLE = throttleRaw;
//  input_ROLL = rollRaw;
//  input_PITCH = pitchRaw;
//  input_YAW = yawRaw;
}
