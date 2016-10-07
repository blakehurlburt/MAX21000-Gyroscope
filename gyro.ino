#include "MAX21K.h"

MAX21K gyro;

void setup() {

  Serial.begin(115200);
  while(!Serial); //waits for serial connection
  
  gyro.init();
  gyro.setFreq(10); //read data at 10 Hz
  
}

void loop() {
  while(!gyro.update()); //waits for new data
  
  Serial.print(F("x: "));
  if (gyro.getX() >= 0.) Serial.print(F(" "));
  Serial.print(gyro.getX());
  Serial.print(F("\ty: "));
  if (gyro.getY() >= 0.) Serial.print(F(" "));
  Serial.print(gyro.getY());
  Serial.print(F("\tz: "));
  if (gyro.getZ() >= 0.) Serial.print(F(" "));
  Serial.println(gyro.getZ());
  
}
