#include "graphics.hpp"

Graphics::Graphics(Display& display, uint16_t width, uint16_t height) : display(display), width(width), height(height) {
}

Graphics& Graphics::drawPoint(uint16_t x, uint16_t y, uint16_t color) {
    display.fillPoint(x, y, color);
    return *this;
}

Graphics& Graphics::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint8_t x_adder = x1 <= x2 ? 1 : -1;
    uint8_t y_adder = y1 <= y2 ? 1 : -1;
    uint8_t ratio = (x1 - x2) / (y1 - y2);
    if (ratio < 0) {
        ratio *= -1;
    }
    for (uint16_t x = 0, y = 0; x <= x2; x += x_adder, y += y_adder) {
        display.fillPoint(x + x1, y * ratio + y1, color);
    }
    return *this;
}

Graphics &Graphics::fillScreen(uint16_t color) {
    display.fillBlock(0, 0, width, height, color);
    return *this;
}

void Graphics::flush() {
}