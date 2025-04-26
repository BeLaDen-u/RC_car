#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "config.h"
#include "servo_control.h"
#include "esc_control.h"

class Communication {
public:
    void setup(ServoControl& servo, ESCControl& esc);
    bool isConnectionTimedOut() const;

private:
    static ServoControl* servoControl;
    static ESCControl* escControl;
    static unsigned long lastComm;
    static const unsigned long COMM_TIMEOUT = 1000;
    static void onDataReceived(const uint8_t* mac, const uint8_t* data, int len);
};

#endif // COMMUNICATION_H