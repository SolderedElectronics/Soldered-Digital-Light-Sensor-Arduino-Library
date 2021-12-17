/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/


#include "Digital-light-sensor-with-easyc-SOLDERED.h"

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Example parameter.
 */
void LTR507::Sensor(int _pin)
{
    pin = _pin;
    native = 1;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void LTR507::initializeNative()
{
    pinMode(pin, INPUT);
}

uint16_t *LTR507::getLightIntensity()
{
    readRegister(ALS_PS_INTERRUPT_ADDRESS, raw, sizeof(uint8_t)); // Get ALS and PS state register
    if (!(0x4 & raw[0])) // If bit 2 is set to 0, Digital Light Sensor measuring is old data
    {
        return 0;
    }
    readRegister(LIGHT_INTENSITY_ADDRESS, raw,
                 sizeof(uint8_t) * 2); // Get two bytes that consist of light intensity data
    value = raw[0] | raw[1] << 8;      // I2C sends 8 bits at once, this function merges two bytes into one variable
    return &value;
}

uint16_t *LTR507::getProximity()
{
    readRegister(ALS_PS_INTERRUPT_ADDRESS, raw, sizeof(uint8_t)); // Get ALS and PS state register
    if (!(0x1 & raw[0])) // If bit 0 is set to 0, Proximity Sensor measuring is old data
    {
        return 0;
    }
    readRegister(PROXIMITY_ADDRESS, raw, sizeof(uint8_t) * 2); // Get two bytes that consist of proximity data
    value = raw[0] | raw[1] << 8; // I2C sends 8 bits at once, this function merges two bytes into one variable
    return &value;
}

bool LTR507::Available()
{
    return sendAddress(ALS_PS_INTERRUPT_ADDRESS);
}

void LTR507::setPSMode(bool mode)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(PS_CONTR_REG, &buff, sizeof(char));
    if (mode)
    {
        reg_state[1] = buff | 0x02;
    }
    else
    {
        reg_state[1] = buff & 0xFD;
    }
    reg_state[0] = PS_CONTR_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

void LTR507::setALSMode(bool mode)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(ALS_CONTR_REG, &buff, sizeof(char));
    if (mode)
    {
        reg_state[1] = buff | 0x02;
    }
    else
    {
        reg_state[1] = buff & 0xFD;
    }
    reg_state[0] = ALS_CONTR_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

char LTR507::getReg(int addr)
{
    char a = 'a';
    readRegister(addr, &a, 1);
    return a;
}

void LTR507::setALSGain(uint8_t state)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(ALS_CONTR_REG, &buff, sizeof(char));
    reg_state[1] = (buff & B11110011) | state << 2;
    reg_state[0] = ALS_CONTR_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

void LTR507::setPSLedDutyCycle(uint8_t state)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(PS_LED_REG, &buff, sizeof(char));
    reg_state[1] = (buff & B00011111) | state << 5;
    reg_state[0] = PS_LED_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

void LTR507::setPSMeasRate(uint8_t rate)
{
    uint8_t reg_state[2];
    reg_state[1] = rate;
    reg_state[0] = PS_MEAS_RATE;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

void LTR507::setNPulses(uint8_t n)
{
    uint8_t reg_state[2];
    reg_state[1] = n;
    reg_state[0] = PS_N_PULSES;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

void LTR507::init()
{
    setALSGain(ALS_GAIN_1);
    setPSLedDutyCycle(PS_LED_FREQ_30);
    setPSMeasRate(PS_MEAS_RATE_100);
    setNPulses(127);
    setPSMode(1);
    setALSMode(1);
}
