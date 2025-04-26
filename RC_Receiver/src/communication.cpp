#include "communication.h"

ServoControl* Communication::servoControl = nullptr;
ESCControl* Communication::escControl = nullptr;
unsigned long Communication::lastComm = 0;

void Communication::setup(ServoControl& servo, ESCControl& esc) {
    servoControl = &servo;
    escControl = &esc;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != ESP_OK) {
        return;
    }

    esp_now_register_recv_cb(onDataReceived);
}

void Communication::onDataReceived(const uint8_t* mac, const uint8_t* data, int len) {
    if (len != sizeof(rc_data_t)) {
        return;
    }

    rc_data_t* rcData = (rc_data_t*)data;
    
    if (servoControl) {
        servoControl->setAngle(rcData->servoAngle);
    }
    if (escControl) {
        escControl->setTargetValue(rcData->escValue);
    }

    lastComm = millis();
}

bool Communication::isConnectionTimedOut() const {
    return (millis() - lastComm) > COMM_TIMEOUT;
}