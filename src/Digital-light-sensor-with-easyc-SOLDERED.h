/**
 **************************************************
 *
 * @file        Digital-light-sensor-with-easyc-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Goran Juric for soldered.com
 ***************************************************/

#ifndef _Light_Sensor_
#define _Light_Sensor_

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

#define LTR507_ADDRESS          0x3A
#define LTR507_SLAVE_ADDRESS    0X23
#define LIGHT_INTENSITY_ADDRESS 0x88
#define PROXIMITY_ADDRESS       0x8B
#define ALS_PS_STATUS_ADDRESS   0x8A
#define ALS_CONTR_REG           0x80
#define PS_CONTR_REG            0x81
#define PS_LED_REG              0X82
#define PS_N_PULSES             0x83
#define ALS_MEAS_RATE           0x85
#define PART_ID_REG             0x86

#define ALS_GAIN_1    B00
#define ALS_GAIN_05   B01
#define ALS_GAIN_001  B10
#define ALS_GAIN_0005 B11

#define ALS_BIT_WIDTH_0 B000 // 1200 ms
#define ALS_BIT_WIDTH_1 B001 // 600 ms
#define ALS_BIT_WIDTH_2 B010 // 300 ms
#define ALS_BIT_WIDTH_3 B011 // 150 ms
#define ALS_BIT_WIDTH_4 B100 // 75 ms
#define ALS_BIT_WIDTH_5 B101 // 4.7 ms
#define ALS_BIT_WIDTH_6 B110 // 292 uS
#define ALS_BIT_WIDTH_7 B111 // 18 uS

#define ALS_MEAS_RATE_0 B000
#define ALS_MEAS_RATE_1 B001
#define ALS_MEAS_RATE_2 B010
#define ALS_MEAS_RATE_3 B011
#define ALS_MEAS_RATE_4 B100

#define PS_MEAS_RATE_12_5 B000
#define PS_MEAS_RATE_50   B001
#define PS_MEAS_RATE_70   B010
#define PS_MEAS_RATE_100  B011
#define PS_MEAS_RATE_200  B100
#define PS_MEAS_RATE_500  B101
#define PS_MEAS_RATE_1000 B110
#define PS_MEAS_RATE_2000 B111

class LTR507 : public EasyC
{
  public:
    void Sensor(int _pin);
    uint16_t getLightIntensity();
    bool Available();
    void setALSMode(bool);
    void setPSMode(bool);
    void init(void);
    void setALSGain(uint8_t);
    char getReg(int addr);
    void setALSMeasRate(uint8_t);
    void setALSBitWidth(uint8_t);

  protected:
    void initializeNative();

  private:
    int pin;
    char raw[2];
};

#endif
