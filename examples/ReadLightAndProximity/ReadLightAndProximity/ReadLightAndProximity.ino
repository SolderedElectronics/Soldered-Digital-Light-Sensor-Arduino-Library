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
  Serial.begin(115200); //Start communication with PC via UART
  sensor.init();        //Initialize sensor
}

void loop()
{
  if(sensor.Available())  //Check if sensor is available
  {
    uint16_t light; 
    light = sensor.getLightIntensity(); // get light intensity
    if(light!=0){
      Serial.print("Light intensity: ");
      Serial.print(light);              // print light intensity
      Serial.println(" lux.");
    }
    else{
      Serial.println("Light intensity is not read or 0 lux.");//If there was some kind of error
                                                              //print message
    }
  }
  else Serial.println("Communication error"); // If sensor is not available,
                                              // there was communication error
  Serial.println("");
  delay(1000);
}
