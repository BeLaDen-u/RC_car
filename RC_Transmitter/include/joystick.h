#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>
#include "config.h"

class Joystick {
public:
    void setup();
    void calibrate();
    void updateValues(rc_data_t& data);

private:
    int joyCenterX = 0;
    int joyCenterY = 0;
    int joyCenterXMin = 0;
    int joyCenterXMax = 0;
    int joyCenterYMin = 0;
    int joyCenterYMax = 0;
    
    int servoReadings[FILTER_SAMPLES];
    int escReadings[FILTER_SAMPLES];
    int readIndex = 0;
    
    esp_adc_cal_characteristics_t adc1_chars;
    
    int getFilteredReading(adc1_channel_t channel, int* readings);
    void updateServoValues(rc_data_t& data, int joyValue);
    void updateESCValues(rc_data_t& data, int joyValue);
};

#endif // JOYSTICK_H