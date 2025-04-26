#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Servo configuration
const uint8_t SERVO_MIN = 28;
const uint8_t SERVO_CENTER = 82;
const uint8_t SERVO_MAX = 123;

// ESC configuration
const uint16_t ESC_MIN = 1000;
const uint16_t ESC_CENTER = 1500;
const uint16_t ESC_MAX = 2000;

// Joystick configuration
const int FILTER_SAMPLES = 4;
const int JOY_DEADZONE = 50;

// Receiver MAC address
const uint8_t receiverMacAddress[] = {0x08, 0xD1, 0xF9, 0xC7, 0x7A, 0x50};

// Data structure
typedef struct __attribute__((packed)) {
    uint8_t servoAngle;   
    uint16_t escValue;   
} rc_data_t;

#endif // CONFIG_H