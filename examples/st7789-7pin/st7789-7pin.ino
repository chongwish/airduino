#include <airduino.h>

#include <devs/st7789_7pin_sw.hpp>
#include <libs/graphics.hpp>

St7789_7pin st7789(PA_5, PA_7, PA_6, PB_1, PB_0);
Graphics graphics(st7789, 240, 240);

void setup() {
    st7789.begin();

    Serial.begin(115200);
}

void loop() {
    graphics.fillScreen(0x00);

    uint16_t color = 0x3f;
    for (int x = 0; x < 240; x += 2) {
        for (int y = 0; y < 240; y += 2) {
            graphics.drawPoint(x, y, color);
            color += 0x3f;
        }
    }
}