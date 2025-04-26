#include <Arduino.h>

const int joystickXAxis = 34;  // Joystick X axis pin (ADC1_6)
const int joystickYAxis = 35;  // Joystick Y axis pin (ADC1_7)
const int SAMPLES = 500;    // Number of samples to take
const int DELAY_MS = 20;    // Delay between samples

// Arrays to store readings for both axes
int readingsX[SAMPLES];     
int readingsY[SAMPLES];     
int currentSample = 0;      
bool calibrationDone = false;

void setup() {
    Serial.begin(115200);
    analogReadResolution(12);
    pinMode(joystickXAxis, INPUT);
    pinMode(joystickYAxis, INPUT);

    Serial.println("Dual Axis Calibration Program");
    Serial.println("Keep joystick centered and still");
    Serial.println("Taking 500 samples...");
}

void loop() {
    if (!calibrationDone && currentSample < SAMPLES) {
        // Take readings from both axes
        readingsX[currentSample] = analogRead(joystickXAxis);
        readingsY[currentSample] = analogRead(joystickYAxis);
        
        Serial.print("Sample ");
        Serial.print(currentSample + 1);
        Serial.print(" X: ");
        Serial.print(readingsX[currentSample]);
        Serial.print(" Y: ");
        Serial.println(readingsY[currentSample]);
        
        currentSample++;
        delay(DELAY_MS);
        
        // Calculate averages when all samples are collected
        if (currentSample == SAMPLES) {
            long sumX = 0, sumY = 0;
            for (int i = 0; i < SAMPLES; i++) {
                sumX += readingsX[i];
                sumY += readingsY[i];
            }
            float averageX = sumX / (float)SAMPLES;
            float averageY = sumY / (float)SAMPLES;
            
            Serial.println("\n--- Calibration Results ---");
            Serial.print("X Center Value: ");
            Serial.println(averageX);
            Serial.print("Y Center Value: ");
            Serial.println(averageY);
            calibrationDone = true;
        }
    }
}