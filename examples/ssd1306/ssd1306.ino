#include <airduino.h>

#include <devices/page_screen.hpp>
#include <drivers/ssd1306.hpp>

Ssd1306 ssd1306;
PageScreen<uint8_t, 128, 64> screen;

void setup() {
    screen.loadDriver(&ssd1306);

    Serial.begin(115200);
    Serial.println("ssd1306");
}

void loop() {
    screen.display(0, 0, 128, 64, (uint8_t)0);

    delay(1000);

    for (int y = 0; y < 64; y += 4) {
        for (int x = 0; x < 128; x += 4) {
            screen.display(x, y, 1);
            delay(50);
        }
    }

    delay(1000);

    for (int y = 0; y < 64; y += 8) {
        for (int x = 0; x < 128; x += 8) {
            screen.cache(x, y, 0);
        }
        delay(50);
        screen.display();
    }

    Serial.println("Over");
    delay(2000);
}