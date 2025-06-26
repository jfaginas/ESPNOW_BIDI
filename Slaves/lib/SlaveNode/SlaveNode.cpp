#include "SlaveNode.h"

bool SlaveNode::begin() {
    display.begin();

    if (!EspNowInterface::begin()) {
        Serial.println("[SLAVE] Falla al inicializar ESPNOW");
        return false;
    }

    // Dirección MAC del master
    uint8_t masterMac[] = {0x10, 0x06, 0x1C, 0xF4, 0xE8, 0x78};

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, masterMac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (!esp_now_is_peer_exist(masterMac)) {
        esp_err_t result = esp_now_add_peer(&peerInfo);
        if (result != ESP_OK) {
            Serial.print("[SLAVE] Error al agregar peer master: ");
            Serial.println(result);
            return false;
        } else {
            Serial.println("[SLAVE] Master agregado como peer");
        }
    }

    return true;
}

void SlaveNode::onDataReceived(const uint8_t *mac, const uint8_t *data, int len) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    String macLine = "SRC " + String(macStr);
    String msgLine = String((char*)data, len);

    display.print(macLine);
    display.print(msgLine);

    Serial.println(macLine);
    Serial.println(msgLine);

    const char *echo = "Echo desde slave";
    bool ok = send(mac, reinterpret_cast<const uint8_t *>(echo), strlen(echo));

    if (ok) {
        Serial.print("[SLAVE] Echo enviado a ");
    } else {
        Serial.print("[SLAVE] FALLO al enviar a ");
    }

    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);

}
