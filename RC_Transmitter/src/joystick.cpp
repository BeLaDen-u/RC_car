#include "joystick.h"

void Joystick::setup() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
  
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc1_chars);
}

void Joystick::calibrate() {
    long sumX = 0, sumY = 0;
    const int samples = 200;
    
    for(int i = 0; i < samples; i++) {
        sumX += adc1_get_raw(ADC1_CHANNEL_6);
        sumY += adc1_get_raw(ADC1_CHANNEL_7);
        delay(20);
    }
    
    joyCenterX = sumX / samples;
    joyCenterY = sumY / samples;
    
    joyCenterXMin = joyCenterX - JOY_DEADZONE;
    joyCenterXMax = joyCenterX + JOY_DEADZONE;
    joyCenterYMin = joyCenterY - JOY_DEADZONE;
    joyCenterYMax = joyCenterY + JOY_DEADZONE;
}

int Joystick::getFilteredReading(adc1_channel_t channel, int* readings) {
    readings[readIndex] = adc1_get_raw(channel);
    int sum = 0;
    for(int i = 0; i < FILTER_SAMPLES; i++) {
        sum += readings[i];
    }
    return sum / FILTER_SAMPLES;
}

void Joystick::updateServoValues(rc_data_t& data, int joyValue) {
    if (joyValue >= joyCenterXMin && joyValue <= joyCenterXMax) {
        data.servoAngle = SERVO_CENTER;
    } else if (joyValue < joyCenterXMin) {
        data.servoAngle = (uint8_t)map(joyValue, 0, joyCenterXMin, SERVO_MIN, SERVO_CENTER);
    } else {
        data.servoAngle = (uint8_t)map(joyValue, joyCenterXMax, 4095, SERVO_CENTER, SERVO_MAX);
    }
}

void Joystick::updateESCValues(rc_data_t& data, int joyValue) {
    if (joyValue >= joyCenterYMin && joyValue <= joyCenterYMax) {
        data.escValue = ESC_CENTER;
    } else if (joyValue < joyCenterYMin) {
        data.escValue = (uint16_t)map(joyValue, 0, joyCenterYMin, ESC_MIN, ESC_CENTER);
    } else {
        data.escValue = (uint16_t)map(joyValue, joyCenterYMax, 4095, ESC_CENTER, ESC_MAX);
    }
}

void Joystick::updateValues(rc_data_t& data) {
    int joyValServo = getFilteredReading(ADC1_CHANNEL_6, servoReadings);
    int joyValESC = getFilteredReading(ADC1_CHANNEL_7, escReadings);
    
    readIndex = (readIndex + 1) % FILTER_SAMPLES;

    updateServoValues(data, joyValServo);
    updateESCValues(data, joyValESC);
}