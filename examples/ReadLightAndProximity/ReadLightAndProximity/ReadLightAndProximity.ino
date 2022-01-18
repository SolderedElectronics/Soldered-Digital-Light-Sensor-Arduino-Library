/**
 **************************************************
 *
 * @file        ReadLightIntensity.ino
 * @brief       Example for reading light intensity
 *
 *
 *
 * @authors     Goran Juric for soldered.com
 ***************************************************/

#include "Digital-light-sensor-with-easyc-SOLDERED.h"

LTR507 sensor;

void setup()
{
  Serial.begin(115200);
  sensor.init();
}

void loop()
{
  if(sensor.Available()){
    uint16_t light; 
    light = sensor.getLightIntensity(); // get light intensity
    if(light!=0){
      Serial.print("Light intensity: ");
      Serial.print(light);
      Serial.println(" lux.");
    }
    else{
      Serial.println("Light intensity is not read or 0 lux.");
    }
  }
  else Serial.println("Communication error");
  Serial.println("");
  delay(1000);
}
