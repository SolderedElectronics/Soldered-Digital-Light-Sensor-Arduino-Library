/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef _Light_Sensor_
#define _Light_Sensor_

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.h"

#define LTR507_ADDRESS           0x74
#define LIGHT_INTENSITY_ADDRESS  0x88
#define PROXIMITY_ADDRESS        0x8B
#define ALS_PS_INTERRUPT_ADDRESS 0x8A
#define ALS_CONTR_REG            0X80
#define PS_CONTR_REG             0X81

class LTR507 : public Digital_light_sensor_easyc::EasyC
{
  public:
    void Sensor(int _pin);
    uint16_t *getLightIntensity();
    uint16_t *getProximity();
    bool Available();
    void setPSMode(bool);
    void setALSMode(bool);
    char getReg(int addr);

  protected:
    void initializeNative();

  private:
    int pin;
    char raw[2];
    uint16_t value;
};

#endif
