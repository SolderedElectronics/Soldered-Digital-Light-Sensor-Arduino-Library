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

#define LTR507_ADDRESS              0x3A
#define LTR507_SLAVE_ADDRESS        0X23
#define LIGHT_INTENSITY_ADDRESS     0x88
#define PROXIMITY_ADDRESS           0x8B
#define ALS_PS_INTERRUPT_ADDRESS    0x8A
#define ALS_CONTR_REG               0x80
#define PS_CONTR_REG                0x81
#define PS_LED_REG                  0X82
#define PS_N_PULSES                 0x83
#define PS_MEAS_RATE                0x84

#define ALS_GAIN_1                  B00
#define ALS_GAIN_05                 B01
#define ALS_GAIN_001                B10
#define ALS_GAIN_0005               B11

#define PS_LED_FREQ_30              B000
#define PS_LED_FREQ_40              B001
#define PS_LED_FREQ_50              B010
#define PS_LED_FREQ_60              B011
#define PS_LED_FREQ_70              B100
#define PS_LED_FREQ_80              B101
#define PS_LED_FREQ_90              B110
#define PS_LED_FREQ_100             B111

#define PS_MEAS_RATE_12_5           B000
#define PS_MEAS_RATE_50             B001
#define PS_MEAS_RATE_70             B010
#define PS_MEAS_RATE_100            B011
#define PS_MEAS_RATE_200            B100
#define PS_MEAS_RATE_500            B101
#define PS_MEAS_RATE_1000           B110
#define PS_MEAS_RATE_2000           B111

class LTR507 : public Digital_light_sensor_easyc::EasyC
{
  public:
    void Sensor(int _pin);
    uint16_t* getLightIntensity();
    uint16_t* getProximity();
    bool Available();
    void setPSMode(bool);
    void setALSMode(bool);
    void init(void);
    void setALSGain(uint8_t);
    void setPSLedDutyCycle(uint8_t);
    void setNPulses(uint8_t);
    void setPSMeasRate(uint8_t);
    char getReg(int addr);

  protected:
    void initializeNative();

  private:
    int pin;
    char raw[2];
    uint16_t value;
};

#endif
