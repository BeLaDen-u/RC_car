#include "esc_control.h"

void ESCControl::setup() {
    ESP32PWM::allocateTimer(1);
    esc.setPeriodHertz(50);
    esc.attach(ESC_PIN, ESC_MIN, ESC_MAX);
    esc.writeMicroseconds(ESC_CENTER);
}

uint16_t ESCControl::processValue(uint16_t rawValue) {
    // Detectar si estamos cerca del centro (añadir deadband)
    if (abs((int)rawValue - ESC_CENTER) < 50) { // 50 microsegundos de deadband
        return ESC_CENTER;
    }

    bool newDirection = (rawValue > ESC_CENTER);
    
    // Si hay cambio de dirección y no estamos en el centro, forzar a neutral
    if (newDirection != isForward && currentValue != ESC_CENTER) {
        return ESC_CENTER;
    }
    
    // Actualizar dirección solo cuando estamos en el centro
    if (currentValue == ESC_CENTER) {
        isForward = newDirection;
    }

    if (rawValue < ESC_MIN) rawValue = ESC_MIN;
    if (rawValue > ESC_MAX) rawValue = ESC_MAX;

    return applyExponentialCurve(rawValue);
}

uint16_t ESCControl::applyExponentialCurve(uint16_t input) {
    // Normalizar el valor de entrada a un rango de -1 a 1
    float normalized = (float)(input - ESC_CENTER) / (float)(ESC_MAX - ESC_CENTER);
    
    // Aplicar la curva exponencial
    float expo = exponentialFactor;
    float output = normalized * (1 - expo) + normalized * normalized * normalized * expo;
    
    // Convertir de vuelta al rango de microsegundos
    uint16_t result = ESC_CENTER + (int16_t)(output * (ESC_MAX - ESC_CENTER));
    
    // Asegurar límites
    if (result < ESC_MIN) result = ESC_MIN;
    if (result > ESC_MAX) result = ESC_MAX;
    
    return result;
}

void ESCControl::setTargetValue(uint16_t value) {
    targetValue = processValue(value);
}

void ESCControl::update() {
    unsigned long currentMillis = millis();

    // 1. Protección térmica
    if (currentValue > HIGH_THROTTLE_THRESHOLD) {
        if (throttleHighTime == 0) {
            throttleHighTime = currentMillis;
        } else if (currentMillis - throttleHighTime > THERMAL_PROTECT_TIME) {
            targetValue = min(targetValue, (uint16_t)(ESC_CENTER + (ESC_MAX - ESC_CENTER) * 0.7));
        }
    } else {
        throttleHighTime = 0;
    }
    
    if ((isForward && targetValue < currentValue) || 
        (!isForward && targetValue > currentValue)) {
        currentValue = ESC_CENTER;
        esc.writeMicroseconds(ESC_CENTER);
        return;
    }
    
    if ((targetValue > ESC_CENTER && currentValue < ESC_CENTER) || 
        (targetValue < ESC_CENTER && currentValue > ESC_CENTER)) {
        currentValue = ESC_CENTER;
        esc.writeMicroseconds(ESC_CENTER);
        return;
    }
    
    if (targetValue > currentValue) {
        currentValue = min((uint16_t)(currentValue + ESC_ACCEL_RAMP_STEP), targetValue);
    } else if (targetValue < currentValue) {
        currentValue = max((uint16_t)(currentValue - ESC_ACCEL_RAMP_STEP), targetValue);
    }

    esc.writeMicroseconds(currentValue);
}

void ESCControl::setFailsafe() {
    esc.writeMicroseconds(ESC_CENTER);
    currentValue = ESC_CENTER;
    targetValue = ESC_CENTER;
    isForward = true;
}