#ifdef ARDUINO_ARCH_AIRMCU
#define CS_PIN PA_4
#define DC_PIN PB_1
#define RST_PIN PA_6
#else
#define CS_PIN 10
#define DC_PIN 9
#define RST_PIN 8
#endif

#include <airduino.h>

#include <devices/screen.hpp>
#include <drivers/st7735.hpp>

St7735 st7735{CS_PIN, DC_PIN, RST_PIN};
Screen<uint16_t, 160, 80> screen;
Coordinate<uint16_t, uint16_t> coordinate{32, 8};

void setup() {
    screen.loadDriver(&st7735);

    Serial.begin(115200);
    Serial.println("st7735");

    screen.display(0, 0, 159, 79, (uint16_t)0x00);
}

void loop() {
    Serial.println("start");

    delay(1000);

    screen.display(8, 8, 71, 71, 0x003f00);
    delay(1000);

    uint16_t color = 0x37;

    for (int y = 8; y < 72; y += 4) {
        for (int x = 8; x < 72; x += 4) {
            /*
            Serial.print("x : ");
            Serial.println(x);
            Serial.print("y : ");
            Serial.println(y);
            Serial.print("color: ");
            Serial.println(color);
            */
            screen.display(x, y, x + 4, y + 4, color);
            color += 0x37;
        }
    }

    delay(1000);

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 32; ++x) {
            coordinate.mark(x, y, color);
            color += 0x37;
        }
    }

    for (int i = 0; i < 4; ++i) {
        screen.display(100, 8 + 8 * i, 132, 8 + (i + 1) * 8, coordinate);
    }

    screen.display(100, 48, 132, 80, [](const uint16_t &x, const uint16_t &y) -> uint16_t {
        return coordinate.getMark(x, y / 4);
    });

    Serial.println("end");
    delay(100000);
}