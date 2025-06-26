#pragma once

#include "EspNowInterface.h"
#include "DebugDisplay.h"

class SlaveNode : public EspNowInterface {
public:
    SlaveNode() = default;
    ~SlaveNode() override = default;

    bool begin();

protected:
    void onDataReceived(const uint8_t *mac, const uint8_t *data, int len) override;

private:
    DebugDisplay display;
};
