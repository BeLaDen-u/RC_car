#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "config.h"

class Communication {
public:
    void setup();
    bool sendData(rc_data_t& data);

private:
    void registerPeers();
};

#endif // COMMUNICATION_H