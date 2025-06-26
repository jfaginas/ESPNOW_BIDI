#pragma once
#include <Arduino.h>
#include "EspNowInterface.h"
#include <vector>

class MasterNode : public EspNowInterface {
public:
    MasterNode() = default;
    ~MasterNode() override = default;

    bool begin();

    void update();  // Llamado desde loop() para hacer envíos periódicos

    // Permite agregar MACs de destino manualmente
    void addPeer(const uint8_t *mac_addr);

protected:
    void onDataReceived(const uint8_t *mac, const uint8_t *data, int len) override;

private:
    std::vector<std::array<uint8_t, 6>> knownPeers;

    unsigned long lastSendTime = 0;
    const unsigned long sendIntervalMs = 5000;

    void sendMessageToAll();
};
