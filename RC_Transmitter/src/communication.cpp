#include "communication.h"

void Communication::setup() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    if(esp_now_init() != ESP_OK)
        return;

    registerPeers();
}

void Communication::registerPeers() {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo) != ESP_OK)
        return;
}

bool Communication::sendData(rc_data_t& data) {
    esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t*)&data, sizeof(rc_data_t));
    return result == ESP_OK;
}