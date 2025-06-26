#pragma once

#include <U8g2lib.h>
#include <Wire.h>

class DebugDisplay {
public:
    DebugDisplay();

    void begin();
    void print(const String &line);  // Agrega una línea al log y actualiza

private:
    static constexpr int MAX_LINES = 6; // Número de líneas visibles en pantalla
    String lines[MAX_LINES];

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

    void refresh();  // Redibuja el contenido en pantalla
};
