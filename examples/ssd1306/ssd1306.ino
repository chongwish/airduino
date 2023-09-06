#include <airduino.h>

#include <devs/ssd1306.hpp>
#include <libs/graphics.hpp>
#include <libs/text.hpp>
#include <libs/color.hpp>

Ssd1306 ssd1306(128, 64, A5, A4);
Graphics<uint8_t> graphics(ssd1306);
Text<uint8_t> text(ssd1306);
Color<uint8_t> color;

void setup() {
    ssd1306.begin();
    
    Serial.begin(9600);
    Serial.println("ssd1306");
}

void loop() {
    graphics.fillScreen(color.white);

    delay(1000);

    graphics.drawRectangle(7, 7, 119, 27, color.black);

    delay(1000);
    
    graphics.drawCircle(63, 47, 16, color.black);

    delay(1000);

    text.color(color.black);

    text.at(21, 13).print("Chongwish");

    delay(1000);

    text.at(39, 39).print("AirMCU!");

    delay(1000);

    for (int x = 0; x < 128; x++) {
        for (int y = 32; y < 64; y++) {
            graphics.drawPoint(x, y, color.black);
        }
    }

    delay(1000);

    for (int x = 0; x < 128; x += 16) {
        graphics.drawLine(0, 31, x, 63, color.white);
        delay(10);
    }

    delay(1000);

    for (int x = 0; x < 128; x += 4) {
        graphics.drawLine(127, 63, x, 31, color.white);
        delay(10);
    }

    delay(1000);
    for (int y = 0; y < 32; y += 4) {
        for (int x = y % 8; x < 128; x += 8) {
            graphics.drawPoint(x, y, color.black);
            delay(50);
        }
    }

    delay(1000);
}