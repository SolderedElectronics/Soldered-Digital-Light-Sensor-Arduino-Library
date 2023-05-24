/**
 **************************************************
 *
 * @file        adjustSettings.ino
 * @brief       This example will show you how to modify parameters of the LTR-507 light sensor
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
    // This function initializes the sensor with the default settings
    sensor.init();

    // You can change the following settings:

    // This turns off the ambient light sensor (ALS) and proximity sensor
    // sensor.setALSMode(false);
    // sensor.setPSMode(false);
    // Setting the parameter to 'true' will turn it back on, this is done by default in init()

    // Set the gain of the sensor
    // This way you can get more or less sensitivity
    // From the datasheet:
    //      -LTR507_ALS_GAIN_RANGE1: 1 lux to 64k lux (1 lux/count) (default)
    //      -LTR507_ALS_GAIN_RANGE2: 0.5 lux to 32k lux (0.5 lux/count)
    //      -LTR507_ALS_GAIN_RANGE3: 0.02 lux to 640 lux (0.01 lux/count)
    //      -LTR507_ALS_GAIN_RANGE4: 0.01 lux to 320 lux (0.005 lux/count)
    sensor.setALSGain(LTR507_ALS_GAIN_RANGE1);

    // Set the automatic measurement rate
    // You can use:
    //      -LTR507_ALS_MEASUREMENT_RATE_100MS (default)
    //      -LTR507_ALS_MEASUREMENT_RATE_200MS
    //      -LTR507_ALS_MEASUREMENT_RATE_500MS
    //      -LTR507_ALS_MEASUREMENT_RATE_1000MS
    //      -LTR507_ALS_MEASUREMENT_RATE_2000MS
    sensor.setALSMeasRate(LTR507_ALS_MEASUREMENT_RATE_100MS);

    // Set the bit width of the ALS measurement
    // This changes the time required to complete a single measurement
    // So, it's reccomended to leave it as default
    // sensor.setALSBitWidth(LTR507_ALS_ADC_BIT_WIDTH_16BIT);

    // Set the auto measurement rate for proximity
    // You can use:
    //      -LTR507_PS_MEASUREMENT_RATE_12_5MS
    //      -LTR507_PS_MEASUREMENT_RATE_50MS
    //      -LTR507_PS_MEASUREMENT_RATE_70MS
    //      -LTR507_PS_MEASUREMENT_RATE_100MS (default)
    //      -LTR507_PS_MEASUREMENT_RATE_200MS
    //      -LTR507_PS_MEASUREMENT_RATE_500MS
    //      -LTR507_PS_MEASUREMENT_RATE_1000MS
    //      -LTR507_PS_MEASUREMENT_RATE_2000MS
    sensor.setPSMeasRate(LTR507_PS_MEASUREMENT_RATE_100MS);

    // Set the max current supplied to the IR LED
    // You can use:
    //      -LTR507_LED_PEAK_CURRENT_5MA
    //      -LTR507_LED_PEAK_CURRENT_10MA
    //      -LTR507_LED_PEAK_CURRENT_20MA
    //      -LTR507_LED_PEAK_CURRENT_50MA (default)
    sensor.setLEDPeakCurrent(LTR507_LED_PEAK_CURRENT_50MA);

    // Set the pulse frequency of the IR LED
    // You can use:
    //      -LTR507_LED_PULSE_FREQ_30KHZ
    //      -LTR507_LED_PULSE_FREQ_40KHZ
    //      -LTR507_LED_PULSE_FREQ_50KHZ
    //      -LTR507_LED_PULSE_FREQ_60KHZ (default)
    //      -LTR507_LED_PULSE_FREQ_70KHZ
    //      -LTR507_LED_PULSE_FREQ_80KHZ
    //      -LTR507_LED_PULSE_FREQ_90KHZ
    //      -LTR507_LED_PULSE_FREQ_100KHZ
    sensor.setLEDPulseFreq(LTR507_LED_PULSE_FREQ_60KHZ);

    // Set the number of pulses for a proximity measurement
    // You can use any number from 1 to 15, default is 1
    sensor.setPSNumPulses(1);
}

void loop()
{
    // Make local variable for reading the light and proximity values
    uint16_t lightReading;
    uint16_t proximityReading;

    // Make readings!
    lightReading = sensor.getLightIntensity();
    proximityReading = sensor.getProximity();

    // Print the readings
    Serial.print("Light sensor reading: ");
    Serial.println(lightReading);

    Serial.print("Proximity reading: ");
    Serial.println(proximityReading);

    Serial.println(); // Newline

    // Wait a bit until the next reading so output isn't too fast
    delay(1000);
}
