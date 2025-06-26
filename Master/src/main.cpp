#include <Arduino.h>
#include "MasterNode.h"

MasterNode master;

void setup() {
    Serial.begin(115200);
    master.begin();
}

void loop() {
    master.update();
}
