#include "EspNowInterface.h"

// Instancia actual del sistema de comunicación
EspNowInterface *EspNowInterface::instance = nullptr;

bool EspNowInterface::begin() {
    if (!WiFi.mode(WIFI_STA)) {
        Serial.println("[ESPNOW] Error al poner WiFi en modo STA");
        return false;
    }

    if (esp_now_init() != ESP_OK) {
        Serial.println("[ESPNOW] Error al inicializar ESPNOW");
        return false;
    }

    instance = this;
    attachCallbacks();

    Serial.println("[ESPNOW] Inicialización exitosa");
    return true;
}

void EspNowInterface::attachCallbacks() {
    esp_now_register_recv_cb(_onDataRecvStatic);
    esp_now_register_send_cb(_onDataSentStatic);
}

bool EspNowInterface::send(const uint8_t *mac_addr, const uint8_t *data, size_t len) {
    esp_err_t result = esp_now_send(mac_addr, data, len);
    return (result == ESP_OK);
}

void EspNowInterface::_onDataRecvStatic(const uint8_t *mac, const uint8_t *data, int len) {
    if (instance) {
        instance->onDataReceived(mac, data, len);
    }
}

void EspNowInterface::_onDataSentStatic(const uint8_t *mac, esp_now_send_status_t status) {
    if (instance) {
        instance->onDataSent(mac, status);
    }
}
