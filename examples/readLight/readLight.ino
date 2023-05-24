/**
 **************************************************
 *
 * @file        readLight.ino
 * @brief       This example will show you how to read the lux value from the light sensor.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Open the Serial monitor at 115200 baud!
 *
 *              Digital light & proximity sensor LTR-507: solde.red/333063
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert @ soldered.com
 ***************************************************/

// Include needed libraries
#include "LTR-507-Light-And-Proximity-Sensor-SOLDERED.h"

/**
 * Connecting diagram:
 *
 * LTR-507                      Dasduino Core / Connect / ConnectPlus
 * VCC------------------------->VCC
 * GND------------------------->GND
 * SCL------------------------->A5/IO5/IO22
 * SDA------------------------->A4/IO4/IO21
 * 
 * Or, simply use an easyC cable!
 * 
 */

// Create sensor object
LTR507 sensor;

void setup()
{
    // Begin Serial for debugging purposes
    Serial.begin(115200);

    // Initialize the sensor!
    sensor.init();
}

void loop()
{
    // Make local variable for reading the light value
    uint16_t lightReading;

    // Make reading!
    lightReading = sensor.getLightIntensity();
    
    // Print the reading
    Serial.print("Light sensor reading: ");
    Serial.println(lightReading);

    // Wait a bit until the next reading so output isn't too fast
    delay(1000);
}
