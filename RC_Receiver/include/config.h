#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Pin definitions
#define SERVO_PIN 25
#define ESC_PIN 26

// Servo configuration
const uint8_t SERVO_CENTER = 82;

// ESC configuration
const uint16_t ESC_CENTER = 1500;
const uint16_t ESC_FULL_RANGE = 500;
const uint8_t SPEED_LIMIT_PERCENT = 22;
const uint16_t ESC_LIMITED_RANGE = (ESC_FULL_RANGE * SPEED_LIMIT_PERCENT) / 100;
const uint16_t ESC_MIN = ESC_CENTER - ESC_LIMITED_RANGE;
const uint16_t ESC_MAX = ESC_CENTER + ESC_LIMITED_RANGE;
const uint16_t ESC_ACCEL_RAMP_STEP = 5;

// Data structure
typedef struct __attribute__((packed)) {
    uint8_t servoAngle;
    uint16_t escValue;
} rc_data_t;

#endif // CONFIG_H