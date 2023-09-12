

//INTERRUPTS
void IRAM_ATTR oneRev(){
  tout = timerRead(RPMTimer_Cfg);//RPM = 4800000000.0/(prescaler*timerRead(RPMTimer_Cfg));
  //Serial.println(timerRead(RPMTimer_Cfg));
  timerWrite(RPMTimer_Cfg,0);
}

/*
void IRAM_ATTR timerOverflow(){
  slow = true;
}
*/

//RUN ONCE CODE
void pinSetup(){
  pinMode(revwire,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(rcsig,INPUT);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  torque.begin(torqueDOUT,torqueSCK);
}

unsigned long awaitRemote(){
  //Do nothing until remote is turned on
  while (pulseIn(rcsig,HIGH,1000000) < 500){
    Serial.println("Awaiting Remote...");
    Serial.println(pulseIn(rcsig,HIGH,1000000));
  }
  return pulseIn(rcsig,HIGH,1000000);
}

void tachometerSetup(){
  attachInterrupt(tachPin,oneRev,RISING);
  RPMTimer_Cfg = timerBegin(0,prescaler,true);//Set up timer zero (64 bit) for .1 microsecond ticks
  timerWrite(RPMTimer_Cfg,0);
  //timerAttachInterrupt(RPMTimer_Cfg, &timerOverflow, true);
  timerAlarmWrite(RPMTimer_Cfg, 60000000, true);//six seconds is overflow
  timerAlarmEnable(RPMTimer_Cfg);
}

void globalTimerSetup(){
  GlobalTimer_Cfg = timerBegin(1,prescaler,true);//Set up timer zero (64 bit) for .1 microsecond ticks
  timerWrite(GlobalTimer_Cfg,0);
  //timerAttachInterrupt(RPMTimer_Cfg, &timerOverflow, true);
  timerAlarmWrite(GlobalTimer_Cfg, 60000000, true);//six seconds is overflow
  timerAlarmEnable(GlobalTimer_Cfg);
}
