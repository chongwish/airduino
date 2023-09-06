#include <airduino.h>

#include <devs/ssd1306.hpp>
#include <libs/graphics.hpp>
#include <libs/color.hpp>

Ssd1306 ssd1306(128, 64, A5, A4);
Graphics<uint8_t> graphics(ssd1306);
Color<uint8_t> color;

void setup() {
    ssd1306.begin();
    
    Serial.begin(9600);
    Serial.println("ssd1306");
}

void loop() {
    graphics.fillScreen(color.white);

    graphics.drawRectangle(4, 4, 100, 20, color.black);
    graphics.drawCircle(60, 30, 20, color.black);

    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 64; y++) {
            graphics.drawPoint(x, y, color.black);
        }
    }

    for (int x = 0; x < 128; x += 10) {
        graphics.drawLine(0, 0, x, 63, color.white);
        delay(10);
    }
    for (int x = 0; x < 128; x += 5) {
        graphics.drawLine(127, 63, x, 0, color.white);
        delay(10);
    }

    for (int y = 0; y < 64; y += 4) {
        for (int x = y % 8; x < 128; x += 8) {
            graphics.drawPoint(x, y, color.white);
            delay(10);
        }
    }

    graphics.drawLine(0, 0, 127, 63, color.black);
    delay(10);
    graphics.drawLine(127, 0, 0, 63, color.black);
    delay(10);
    graphics.drawLine(10, 32, 100, 32, color.black);
    delay(10);
    graphics.drawLine(10, 32, 10, 63, color.black);

    delay(10000);
}