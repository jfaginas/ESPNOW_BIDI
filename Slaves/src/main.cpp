#include <Arduino.h>
#include "SlaveNode.h"

SlaveNode slave;

void setup() {
    Serial.begin(115200);
    if (!slave.begin()) {
        Serial.println("[SLAVE] Error durante inicialización. Reiniciando...");
        delay(3000);
        ESP.restart();  // O detener el programa con loop vacío
    }
}

void loop() {}