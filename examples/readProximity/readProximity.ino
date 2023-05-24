/**
 **************************************************
 *
 * @file        readProximity.ino
 * @brief       This example will show you how to read the proximitry from the light sensor.
 *              The sensor is able to measure infra red reflection from an object near it.
 *              This way it can read the proximity of a nearby object.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Also connect the IR LED, info below
 *              -Open the Serial monitor at 115200 baud!
 *
 *              Digital light & proximity sensor LTR-507: solde.red/333063
 *              IR LED: www.solde.red/101922
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
 * IMPORTANT: an IR LED must be connected!
 * LTR-507                      IR LED
 * VLED------------------------>CATHODE (-)
 * VCC------------------------->ANODE (+)
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
    // Make local variable for reading the proximity
    uint16_t proximityReading;

    // Make reading!
    proximityReading = sensor.getProximity();
    
    // Print the reading
    Serial.print("Proximity reading: ");
    Serial.println(proximityReading);

    // Wait a bit until the next reading so output isn't too fast
    delay(1000);
}
