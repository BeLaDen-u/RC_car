#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"

class ServoControl {
public:
    void setup();
    void setAngle(uint8_t angle);
    void setFailsafe();

private:
    Servo servo;
};

#endif // SERVO_CONTROL_H