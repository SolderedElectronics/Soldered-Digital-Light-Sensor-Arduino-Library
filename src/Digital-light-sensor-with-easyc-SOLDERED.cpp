/**
 **************************************************
 *
 * @file        Digital-light-sensor-with-easyc-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Goran Juric for soldered.com
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

/**
 * @brief                   Function which gets light intensity data through I2C communication
 *                          and converts it to int
 *
 * @return                  light intensity
 */
uint16_t LTR507::getLightIntensity()
{
    readRegister(ALS_PS_STATUS_ADDRESS, raw, sizeof(uint8_t)); // Get ALS and PS state register
    if (!(0x4 & raw[0])) // If bit 2 is set to 0, Digital Light Sensor measuring is already read
    {
        return 0;
    }
    readRegister(LIGHT_INTENSITY_ADDRESS, raw,
                 sizeof(uint8_t) * 2); // Get two bytes that consist of light intensity data
    return raw[0] | raw[1] << 8;      // I2C sends 8 bits at once, this function merges two bytes into one variable
}

/**
 * @brief                   Function which checks if I2C device is responding
 *
 * @return                  1 if device is responding, 0 if not
 */
bool LTR507::Available()
{
    return !(sendAddress(PART_ID_REG)); //checking if address is succesfully sent, if not device is not ready to communicate
}

/**
 * @brief                   Function that enables or disables ALS measurements
 *
 * @param bool _mode         1 for enable, 0 for disable                 
 */
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

/**
 * @brief                   Function that enables or disables ALS measurements and is not used here
 *
 * @param bool _mode         1 for enable, 0 for disable               
 */
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
    sendData(reg_state, sizeof(uint8_t)*2);
}

/**
 * @brief                   Function that fetches specific register data
 *
 * @param int _addr          Example parameter.
 *
 * @return                  specific register data
 */
char LTR507::getReg(int addr)
{
    char a = 'a';
    readRegister(addr, &a, 1);
    return a;
}

/**
 * @brief                   Function that sets ALS Gain
 *
 * @param uint8_t _state          Binary code from macro defines              
 */
void LTR507::setALSGain(uint8_t state)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(ALS_CONTR_REG, &buff, sizeof(char));
    reg_state[1] = (buff & B11110011) | state << 2;
    reg_state[0] = ALS_CONTR_REG;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

/**
 * @brief                   Function that sets resolution of measuring in bits
 *
 * @param uint8_t _rate          Binary code from macro defines                   
 */
void LTR507::setALSBitWidth(uint8_t rate)
{
    uint8_t reg_state[2];
    char buff;
    readRegister(ALS_MEAS_RATE, &buff, sizeof(char));
    reg_state[1] = (buff & B00011111) | rate << 5 ;
    reg_state[0] = ALS_MEAS_RATE;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

/**
 * @brief                   Function which sets time needed to update data register
 *
 * @param uint8_t _rate          Binary code from macro defines
 *
 * @return                  
 */
void LTR507::setALSMeasRate(uint8_t rate){
    uint8_t reg_state[2];
    char buff;
    readRegister(ALS_MEAS_RATE, &buff, sizeof(char));
    reg_state[1] = (buff & B11111000) | rate ;
    reg_state[0] = ALS_MEAS_RATE;
    sendData(reg_state, sizeof(uint8_t) * 2);
}

/**
 * @brief                   Function which initializes sensor
 * 
 */
void LTR507::init()
{
    begin(LTR507_ADDRESS);
    setALSMode(1);
    setPSMode(1);
    setALSGain(ALS_GAIN_1);
    setALSBitWidth(ALS_BIT_WIDTH_4);
    setALSMeasRate(ALS_MEAS_RATE_2);
}
