# ESP-NOW Bidireccional – Master & Slaves

Este proyecto es una prueba de concepto funcional de comunicación bidireccional usando ESP-NOW entre un ESP32 Master y múltiples ESP32 Slaves.

## 📦 Estructura del proyecto
```text
ESPNOW_BIDI/
├── Master/ # Firmware para la placa principal (envía y recibe)
└── Slaves/ # Firmware para nodos esclavos con pantalla OLED para debug
```

Cada subcarpeta contiene su propio `platformio.ini`, `src/` y `lib/`.

## 🔧 Requisitos

- ESP32 (Master y Slaves)
- Display OLED SSD1306 I2C para cada slave (usado solo en esta etapa para debug)
- PlatformIO + VSCode
- Conexiones:
  - SDA → GPIO21
  - SCL → GPIO22
  - VCC → 3.3V
  - GND → GND

## 📡 Funcionamiento

- El Master envía mensajes periódicamente a los slaves.
- Cada Slave responde con un echo que el master recibe.
- El slave muestra en su display OLED:
  - MAC del remitente
  - Texto recibido

## ⚠️ Importante

- El firmware de los **slaves es el mismo para todos**.
- En cada firmware, recordá definir correctamente las **MACs de los peers**.
- Cada slave debe agregar la MAC del master como peer para poder responderle.

## 🧪 Estado actual

✅ Comunicación ESPNOW bidireccional  
✅ Display OLED para debug  
✅ Código limpio, separado por responsabilidad  
⏭️ Próxima etapa: autodetección dinámica de nodos en el master


## 📖 Licencia

Este proyecto está licenciado bajo la licencia MIT.

## 👤 Autor

Es un ejercicio educativo desarrollado por José Faginas, usando el siguiente toolchain: VsCode + PlatformIO en C++.
