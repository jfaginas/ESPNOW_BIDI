#include "MasterNode.h"

bool MasterNode::begin() {
    if (!EspNowInterface::begin()) return false;

    // MACs de los SLAVES (por ahora hardcodeadas)
    uint8_t mac1[6] = { 0x10, 0x06, 0x1C, 0xF4, 0xC2, 0xC0 };
    uint8_t mac2[6] = { 0x10, 0x06, 0x1C, 0xF4, 0x5A, 0xBC };

    addPeer(mac1);
    addPeer(mac2);
    Serial.print("[MASTER] Peers conocidos: ");
    Serial.println(knownPeers.size());  
    return true;
}

void MasterNode::addPeer(const uint8_t *mac_addr) {

    std::array<uint8_t, 6> peer;
    memcpy(peer.data(), mac_addr, 6);
    knownPeers.push_back(peer);

    Serial.print("[MASTER] Agregando peer: ");
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac_addr[0], mac_addr[1], mac_addr[2],
             mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.println(macStr);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, mac_addr, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (!esp_now_is_peer_exist(mac_addr)) {
        esp_now_add_peer(&peerInfo);
    }
}

void MasterNode::update() {
    if (millis() - lastSendTime >= sendIntervalMs) {
        lastSendTime = millis();
        sendMessageToAll();
    }
}

void MasterNode::sendMessageToAll() {

    // Serial.println("[MASTER] Entrando en sendMessageToAll()"); // DEBUG
    const char *msg = "Hola desde master";
    for (const auto &mac : knownPeers) {
        send(mac.data(), reinterpret_cast<const uint8_t *>(msg), strlen(msg));
        Serial.print("[MASTER] Enviado a: ");
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.println(macStr);
    }
}

void MasterNode::onDataReceived(const uint8_t *mac, const uint8_t *data, int len) {
    Serial.print("[MASTER] Respuesta de ");
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print(macStr);
    Serial.print(" => ");

    for (int i = 0; i < len; ++i) {
        Serial.write(data[i]);
    }
    Serial.println();
}
