#include "../airduino.h"
#include "coordinate.hpp"
#include "display.hpp"

#ifndef AIRDUNIO_LIB_GRAPHICS

#define AIRDUNIO_LIB_GRAPHICS 1

template<typename T>
class Graphics {
    public:
        Graphics<T>(Display<T>& display);
        Graphics<T>& drawPoint(uint16_t x, uint16_t y, T color);
        Graphics<T>& drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, T color);
        Graphics<T>& drawCircle(uint16_t x, uint16_t y, uint16_t radius, T color);
        Graphics<T>& drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, T color);
        Graphics<T>& fillScreen(T color);
        void flush();
    private:
        Display<T>& display;
};

template<typename T>
Graphics<T>::Graphics(Display<T>& display) : display(display) {
}

template<typename T>
Graphics<T>& Graphics<T>::drawPoint(uint16_t x, uint16_t y, T color) {
    display.fillPoint(x, y, color);
    return *this;
}

template<typename T>
Graphics<T>& Graphics<T>::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, T color) {
    int8_t x_adder = x1 <= x2 ? 1 : -1;
    int8_t y_adder = y1 <= y2 ? 1 : -1;
    if (x1 == x2) {
        for (int16_t y = 0; y != y2 - y1; y += y_adder) {
            display.fillPoint(x1, y1 + y, color);
        }
    } else if (y1 == y2) {
        for (int16_t x = 0; x != x2 - x1; x += x_adder) {
            display.fillPoint(x1 + x, y1, color);
        }
    } else {
        uint16_t x_length = (x2 - x1) * x_adder;
        uint16_t y_length = (y2 - y1) * y_adder;
        if (x_length >= y_length) {
            double ratio = (double) (int) (y2 - y1) / (int) (x2 - x1);
            for (int16_t x = 0; x != x2 - x1; x += x_adder) {
                display.fillPoint(x1 + x, y1 + ratio * x, color);
            }
        } else {
            double ratio = (double) (int) (x2 - x1) / (int) (y2 - y1);
            for (int16_t y = 0; y != y2 - y1; y += y_adder) {
                display.fillPoint(x1 + ratio * y, y1 + y, color);
            }
        }
    }
    return *this;
}

template <typename T>
Graphics<T> &Graphics<T>::drawCircle(uint16_t x, uint16_t y, uint16_t radius, T color) {
    drawPoint(x, y - radius, color);
    drawPoint(x, y + radius, color);
    for (int i = 1; i < radius; i++) {
        double angle = PI / 2 * (radius - i) / radius;
        int j = radius * cos(angle);
        int k = radius * sin(angle);
        drawPoint(x + k, y + j, color);
        drawPoint(x + k, y - j, color);
        drawPoint(x - k, y - j, color);
        drawPoint(x - k, y + j, color);
    }
    drawPoint(x - radius, y, color);
    drawPoint(x + radius, y, color);
}

template <typename T>
Graphics<T> &Graphics<T>::drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, T color) {
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y1, x1, y2, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x2, y1, x2, y2, color);
}

template <typename T>
Graphics<T> &Graphics<T>::fillScreen(T color)
{
    display.fillBlock(0, 0, display.getWidth() - 1, display.getHeight() - 1, color);
    return *this;
}

template<typename T>
void Graphics<T>::flush() {
}

#endif