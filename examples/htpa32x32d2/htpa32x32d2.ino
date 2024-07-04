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

    st7735.display(0, 0, 159, 79, (uint16_t)0xffff);
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
        uint8_t red = 0u;
        uint8_t green = 0u;
        uint8_t blue = 0u;

        if (t < 0u) {
            // black;
            red = 0u;
            green = 0u;
            blue = 0u;

        } else if (t < 100u) {
            // blue
            blue = t * 31u / 100;
            if (blue < 16u) {
                blue += 16u;
            } else {
                red = blue - 15u;
                green = red;
                blue = 31u;
            }
        } else if (t < 200u) {
            // aqua
            green = (t - 100u) * 31u / 100;
            if (green < 16u) {
                green += 16u;
            } else {
                red = green - 15u;
                blue = red;
                green = 31u;
            }
            blue += 15u;
        } else if (t < 300u) {
            // green
            green = (t - 200u) * 31u / 100;
            if (green < 16u) {
                green += 16u;
            } else {
                red = green - 15u;
                blue = red;
                green = 31u;
            }
        } else if (t < 400u) {
            // yellow
            red = (t - 300u) * 31u / 100;
            if (red < 16u) {
                red += 16u;
            } else {
                blue = red - 15u;
                green = blue;
                red = 31u;
            }
            green += 15u;
        } else if (t < 500u) {
            // red
            red = (t - 400u) * 31u / 100;
            if (red < 16u) {
                red += 16u;
            } else {
                blue = red - 15u;
                green = blue;
                red = 31u;
            }
        } else if (t < 600u) {
            // purple
            blue = (t - 500u) * 31u / 100;
            if (blue < 16u) {
                blue += 16u;
            } else {
                red = blue - 15u;
                green = red;
                blue = 31u;
            }
            red += 15u;
        } else {
            red = 31u;
            green = 31u;
            blue = 31u;
        }
        return (red << 11) | (green << 5) | blue;
    });

    delay(100);
}