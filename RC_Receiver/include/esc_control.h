#ifndef ESC_CONTROL_H
#define ESC_CONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"

class ESCControl {
public:
    void setup();
    void setTargetValue(uint16_t value);
    void update();
    void setFailsafe();

private:
    Servo esc;
    uint16_t currentValue = ESC_CENTER;
    uint16_t targetValue = ESC_CENTER;
    bool isForward = true;
    unsigned long lastUpdate = 0;

    unsigned long throttleHighTime = 0;
    const unsigned long THERMAL_PROTECT_TIME = 10000;
    const uint16_t HIGH_THROTTLE_THRESHOLD = ESC_CENTER + (ESC_MAX - ESC_CENTER) * 0.8;

    uint16_t processValue(uint16_t rawValue);
    uint16_t applyExponentialCurve(uint16_t input);
    float exponentialFactor = 0.8; // valor entre 0.0 y 1.0
};

#endif // ESC_CONTROL_H