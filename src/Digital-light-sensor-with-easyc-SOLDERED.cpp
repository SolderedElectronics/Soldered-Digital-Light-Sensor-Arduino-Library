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

uint16_t* LTR507::getLightIntensity()
{
    readRegister(ALS_PS_INTERRUPT_ADDRESS, raw, sizeof(uint8_t)); //Get ALS and PS state register
    if (!(0x4 & raw[0])) //If bit 3 is set to 0, Digital Light Sensor measuring is old data
    {
        return 0;
    }
    readRegister(LIGHT_INTENSITY_ADDRESS, raw, sizeof(uint8_t)*2); //Get two bytes that consist of light intensity data
    value = raw[0] | raw[1] << 8; //I2C sends 8 bits at once, this function merges two bytes into one variable
    return &value;
}

uint16_t* LTR507::getProximity()
{
    readRegister(ALS_PS_INTERRUPT_ADDRESS, raw, sizeof(uint8_t)); // Get ALS and PS state register
    if (!(0x1 & raw[0])) // If bit 1 is set to 0, Proximity Sensor measuring is old data
    {
        return 0;
    }
    readRegister(PROXIMITY_ADDRESS, raw, sizeof(uint8_t) * 2); // Get two bytes that consist of proximity data
    value = raw[0] | raw[1] << 8; //I2C sends 8 bits at once, this function merges two bytes into one variable
    return &value;  
}

bool LTR507::Available()
{
    return sendAddress(ALS_PS_INTERRUPT_ADDRESS);
}

void LTR507::setPSMode(bool mode)
{
    uint8_t prev_reg_stat;
    char buff;
    readRegister(PS_CONTR_REG, &buff, sizeof(char));
    prev_reg_stat ^= (-mode ^ buff) & (1LL << 1);
    sendAddress(PS_CONTR_REG);
    sendData(&prev_reg_stat, sizeof(char));
}

void LTR507::setALSMode(bool mode)
{
    uint8_t prev_reg_stat;
    char buff;
    readRegister(ALS_CONTR_REG, &buff, sizeof(char));
    prev_reg_stat ^= (-mode ^ buff) & (1LL << 1);
    sendAddress(ALS_CONTR_REG);
    sendData(&prev_reg_stat, sizeof(char));
}

char LTR507::getReg(int addr)
{
    char a;
    readRegister(addr, &a, 1);
    return a;
}