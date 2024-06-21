#ifdef ARDUINO_ARCH_AIRMCU
#define SCK_PIN PA_5
#define SDA_PIN PA_7
#define RST_PIN PA_6
#define DC_PIN PA_1
#define BLK_PIN PA_0
#else
#define SCK_PIN PIN_A1
#define SDA_PIN PIN_A2
#define RST_PIN PIN_A3
#define DC_PIN PIN_A4
#define BLK_PIN PIN_A5
#endif

#include <airduino.h>

#include <devices/screen.hpp>
#include <drivers/soft/st7789_7pin.hpp>

using namespace soft;

St7789_7pin st7789{SCK_PIN, SDA_PIN, RST_PIN, DC_PIN, BLK_PIN};
Screen<uint16_t, 240, 240> screen;

void setup() {
    screen.loadDriver(&st7789);

    Serial.begin(115200);
    Serial.println("st7789");
}

void loop() {
    Serial.println("start");
    uint16_t color = 0x3f;
    for (int x = 0; x < 240; x += 2) {
        for (int y = 0; y < 240; y += 2) {
            Serial.print("x : ");
            Serial.println(x);
            Serial.print("y : ");
            Serial.println(y);
            Serial.print("color: ");
            Serial.println(color);
            screen.display(x, y, color);
            color += 0x3f;
        }
    }
    Serial.println("end");
    delay(100000);
}