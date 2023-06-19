void SetupPID(){
  
}

void LoopPID(){
  roll_error = AngleRoll - input_ROLL;
  roll_integral += roll_error;
  roll_derivative = roll_error - roll_previous_error;
  roll_previous_error = roll_error;
  rollAdjusted = roll_Kp * roll_error + roll_Ki * roll_integral + roll_Kd * roll_derivative;
  Serial.println(rollAdjusted);

  pitch_error = AnglePitch - input_PITCH;
  pitch_integral += pitch_error;
  pitch_derivative = pitch_error - pitch_previous_error;
  pitch_previous_error = pitch_error;
  pitchAdjusted = pitch_Kp * pitch_error + pitch_Ki * pitch_integral + pitch_Kd * pitch_derivative;
  Serial.println(rollAdjusted);
//  yaw_error = AngleYaw - input_YAW;
//  yaw_integral += yaw_error;
//  yaw_derivative = yaw_error - yaw_previous_error;
//  yaw_previous_error = yaw_error;
//  float adjustedYaw = yaw_Kp * yaw_error + yaw_Ki * yaw_integral + yaw_Kd * yaw_derivative;
}
