//ARDUINO LOBRARIES
#include <SPI.h>
#include <SD.h>

//LOCAL HEADER FILES
#include "Globals.h"
  #include "Setup_Functions.h"
  #include "Measure_Inputs.h"
  #include "Data_Out.h"

void setup() {
  pinSetup();
  Serial.begin(115200);
  SD.begin(ChipSelect);
  offset = awaitRemote();

  //Tare the torque sensor
  torque.set_scale(torqueScaleFactor);
  torque.tare();
  tachometerSetup();
  
}

void loop() {
  for (int i = 0; i<readsperline; i++){
    //READ RC REMOTE
    absthrottle = getThrottle();
    //CONTROL MOTOR PWM SIGNAL
    setMotorSpeed(absthrottle);
    //READ TORQUE
    Q = getTorqueAvg(nTorqueReadings);
    //READ RPM
    RPM = 4800000000.0/(prescaler*tout);

    
    globaltime = timerRead(RPMTimer_Cfg)/10000000.0;//Convert to seconds
    //ifwrite = logData("Propeller/data.txt",absthrottle,Q,RPM,globaltime);
    displayValues(absthrottle,Q,RPM,ifwrite,globaltime);

  }
  

  //DISPLAY
  if (absthrottle < 0.01){
    torque.tare();
  }
  //delay(1);
}
