void displayValues(float th,float q,float rpm, bool write,float time){
  Serial.print("Motor Power: ");
  Serial.print(th*100);
  Serial.print("%  |  Torque: ");
  Serial.print(q*1000);
  Serial.print(" mNm  |  RPM: ");
  Serial.print(round(rpm),0);
  Serial.print("  |  Time: ");
  Serial.print(time);
  Serial.print("  |  Writing: ");
  Serial.println(write);
}

bool logData(String filename,float th,float q,float rpm,float time){
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.print(time);
    return true;
  } else {
    return false;
  }
}