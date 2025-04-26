#include "servo_control.h"

void ServoControl::setup() {
    ESP32PWM::allocateTimer(0);
    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN, 500, 2400);
    servo.write(SERVO_CENTER);
}

void ServoControl::setAngle(uint8_t angle) {
    servo.write(angle);
}

void ServoControl::setFailsafe() {
    servo.write(SERVO_CENTER);
}