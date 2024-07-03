#define CS_PIN PA_4
#define DC_PIN PB_1
#define RST_PIN PA_6

#include <airduino.h>

#include <devices/screen.hpp>
#include <drivers/st7735.hpp>

// uint8_t data[512]{};
uint8_t data[512]{};
uint8_t p[64];

HardwareSerial Serial2(PA1, PA0);

St7735 st7735{CS_PIN, DC_PIN, RST_PIN};
Screen<uint16_t, 160, 80> screen;

void setup() {
    screen.loadDriver(&st7735);

    Serial2.begin(115200);
    Serial2.setTimeout(5000);

    screen.display(0, 0, 159, 79, (uint16_t)0x00);
}

void loop() {
    Serial2.print("VCMD=DAT");

    Serial2.readBytes(p, 5);

    uint16_t i = 0u;
    for (uint8_t y = 0u; y < 24u; y++) {
        Serial2.readBytes(p, 64);
        if (y >= 8) {
            for (uint8_t x = 16u; x < 48u; ++x) {
                data[i++] = p[x];
            }
        }
    }

    screen.display(40, 10, 104, 74, [](const uint16_t &x, const uint16_t &y) -> uint16_t {
        uint16_t index = x / 4u * 2u + y / 4u * 32u;
        uint16_t t = (data[index]) | (data[index + 1] << 8);

        if (t < 300u) {
            return 1u << 11;
        } else if (t > 400u) {
            return 31u << 11;
        }

        uint16_t t1 = (t - 300u) * 31u / 100;
        return t1 << 11;
    });

    delay(100);
}