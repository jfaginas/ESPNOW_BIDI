#pragma once

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class EspNowInterface {
public:
    EspNowInterface() = default;
    virtual ~EspNowInterface() = default;

    bool begin();  // Inicializa WiFi y ESPNOW

    // Enviar datos a una MAC determinada
    bool send(const uint8_t *mac_addr, const uint8_t *data, size_t len);

protected:
    // Estos métodos deben ser sobreescritos por clases derivadas
    virtual void onDataReceived(const uint8_t *mac, const uint8_t *data, int len) = 0;
    virtual void onDataSent(const uint8_t *mac, esp_now_send_status_t status) {}

private:
    // Callbacks estáticos requeridos por la API C de ESPNOW
    static void _onDataRecvStatic(const uint8_t *mac, const uint8_t *data, int len);
    static void _onDataSentStatic(const uint8_t *mac, esp_now_send_status_t status);

    // Singleton implícito (instancia actual)
    static EspNowInterface *instance;

    // Asocia las callbacks C con métodos de instancia
    void attachCallbacks();
};
