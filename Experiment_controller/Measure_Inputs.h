float getThrottle(){
  int rcin = (pulseIn(rcsig,HIGH,100000)-offset);
  if (rcin > rcdeadzone){
    throttle = throttle + throttlesensitivity*(rcin*rcin);
    if (throttle > 50000000){
      throttle = 50000000;
    }
  }
  if (rcin < -rcdeadzone){
    throttle = throttle - throttlesensitivity*(rcin*rcin);
    if (throttle < -0000000){
      throttle = -0000000;
    }
  }
  return throttle/50000000;
}

void setMotorSpeed(float throttleFrac){
  float pwm =.040;//make a global?
  if (throttleFrac > motordeadzone){
    pwm = .04985 + throttleFrac*.05565;
    ledcWrite(ledChannel,pwm*(pow(2,resolution)-1));
    digitalWrite(revwire,0);
  } else if (throttleFrac < -motordeadzone ){
    pwm = .04985 - throttleFrac*.05565;
    ledcWrite(ledChannel,pwm*(pow(2,resolution)-1));
    digitalWrite(revwire,1);
  } else if(throttleFrac>0.0){
    ledcWrite(ledChannel,pwm*(pow(2,resolution)-1));
    digitalWrite(revwire,0);
  } else {
    ledcWrite(ledChannel,pwm*(pow(2,resolution)-1));
    digitalWrite(revwire,1);
  }
}

float getTorqueAvg(int numreadings){
  float sum = 0;
  
  for (int i = 0; i<(numreadings-2); i++){
    Qs[i] = Qs[i+1];
    sum = sum + Qs[i];
  }
  Qs[nTorqueReadings-1] = torque.get_units(1);
  sum = sum + Qs[nTorqueReadings-1];

  float AvgQ = sum/nTorqueReadings;

  if (AvgQ > 400.0){
    AvgQ = AvgQ*0.0000173077251;//(Q-400.0)*0.0000096217306;
  }else if (AvgQ < -400.0){
    AvgQ = AvgQ*0.0000173077251;//(Q+400)*0.00001347214;
  }else{
    AvgQ = AvgQ*0.0000173077251;//0.0;
  }

  return AvgQ;
}