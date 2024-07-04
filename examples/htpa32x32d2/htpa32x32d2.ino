#define CS_PIN PA_4
#define DC_PIN PB_1
#define RST_PIN PA_6

#include <airduino.h>

#include <drivers/st7735.hpp>

uint8_t data[800]{};
uint8_t p[64];

HardwareSerial Serial2(PA1, PA0);

St7735 st7735{CS_PIN, DC_PIN, RST_PIN};

void setup() {
    st7735.initialize();

    Serial2.begin(115200);
    Serial2.setTimeout(5000);

    st7735.display(0, 0, 159, 79, (uint16_t)0x00);
}

void loop() {
    Serial2.print("VCMD=DAT");

    Serial2.readBytes(p, 5);

    uint16_t i = 0u;
    for (uint8_t y = 0u; y < 26u; y++) {
        Serial2.readBytes(p, 64);
        if (y >= 6) {
            for (uint8_t x = 12u; x < 52u; ++x) {
                data[i++] = p[x];
            }
        }
    }

    st7735.display(0, 0, 160, 80, [](const uint16_t &x, const uint16_t &y) -> uint16_t {
        uint16_t index = x / 8u * 2u + y / 4u * 40u;
        uint16_t t = (data[index]) | (data[index + 1] << 8);

        if (t < 0u) {
            // black
            return 0u;
        } else if (t < 100u) {
            // blue
            return t * 31u / 100;
        } else if (t < 200u) {
            // aqua
            return (((t - 100u) * 31u / 100) << 5) | 31u;
        } else if (t < 300u) {
            // green
            return ((t - 200u) * 31u / 100) << 5;
        } else if (t < 400u) {
            // yellow
            return (((t - 300u) * 31u / 100) << 11) | (31u << 5);
        } else if (t < 500u) {
            // red
            return ((t - 400u) * 31u / 100) << 11;
        } else if (t < 600u) {
            // purple
            return ((t - 500u) * 31u / 100) | (31u << 11);
        } else {
            return (31u << 11) | (31u << 6) | 31u;
        }
    });

    delay(100);
}