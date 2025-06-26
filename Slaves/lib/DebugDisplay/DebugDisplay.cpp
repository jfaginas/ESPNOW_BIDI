#include "DebugDisplay.h"

DebugDisplay::DebugDisplay()
    : u8g2(U8G2_R0, U8X8_PIN_NONE) {}

void DebugDisplay::begin() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 10, "OLED READY");
    u8g2.sendBuffer();
    delay(500);  // Para que se vea antes del primer mensaje
}

void DebugDisplay::print(const String &line) {
    String clipped = line.substring(0, 21);  // 21 caracteres máx por línea
    for (int i = 0; i < MAX_LINES - 1; ++i) {
        lines[i] = lines[i + 1];
    }
    lines[MAX_LINES - 1] = clipped;

    refresh();
}

void DebugDisplay::refresh() {
    u8g2.clearBuffer();
    for (int i = 0; i < MAX_LINES; ++i) {
        u8g2.drawStr(0, (i + 1) * 10, lines[i].c_str());
    }
    u8g2.sendBuffer();
}
