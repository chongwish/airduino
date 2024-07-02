#include <airduino.h>
#include <math.h>

#include <devices/page_screen.hpp>
#include <drivers/ssd1306.hpp>

Ssd1306 ssd1306;
PageScreen<uint8_t, 128, 64> screen;

uint8_t pos_y[128]{};
uint8_t p_x = 0;

void setup() {
    screen.loadDriver(&ssd1306);

    Serial.begin(115200);
    Serial.println("ssd1306");

    int y = 0;
    for (int x = 0; x < 128; ++x) {
        y = sin(PI / 2 / 16 * x) * 30 + 30;
        pos_y[x] = y;
        screen.cache(x, y, 1);
    }
    screen.display();
}

void loop() {
    p_x = ++p_x % 128;

    screen.cache(0, pos_y[0], 0);
    for (int x = 1; x < 128; ++x) {
        screen.cache(x - 1, pos_y[x], 1);
        screen.cache(x, pos_y[x], 0);
        pos_y[x - 1] = pos_y[x];
    }
    pos_y[127] = sin(PI / 2 / 16 * p_x) * 30 + 30;
    screen.cache(127, pos_y[127], 1);

    screen.display();
}