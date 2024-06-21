#ifndef AIRDUNIO_APP_GRAPHICS
#define AIRDUNIO_App_GRAPHICS 1

#include "../airduino.h"
#include "../devices/screen.hpp"

template <typename P, typename C>
class Graphics {
    ScreenDisplay<P, C> *screen;

public:
    void use(ScreenDisplay<P, C> *screen);
    void drawPoint(P x, P y, C color);
    void drawLine(P x1, P y1, P x2, P y2, C color);
    void drawCircle(P x, P y, P radius, C color);
    void drawRectangle(P x1, P y1, P x2, P y2, C color);
    void fillScreen(C color);
};

template <typename P, typename C>
void Graphics<P, C>::use(ScreenDisplay<P, C> *screen) {
    this->screen = screen;
}

template <typename P, typename C>
inline void Graphics<P, C>::drawPoint(P x, P y, C color) {
    screen->cache(x, y, color);
    screen->display();
}

template <typename P, typename C>
inline void Graphics<P, C>::drawLine(P x1, P y1, P x2, P y2, C color) {
    int8_t x_adder = x1 <= x2 ? 1 : -1;
    int8_t y_adder = y1 <= y2 ? 1 : -1;
    if (x1 == x2) {
        for (int16_t y = 0; y != y2 - y1; y += y_adder) {
            screen->cache(x1, y1 + y, color);
        }
    } else if (y1 == y2) {
        for (int16_t x = 0; x != x2 - x1; x += x_adder) {
            screen->cache(x1 + x, y1, color);
        }
    } else {
        uint16_t x_length = (x2 - x1) * x_adder;
        uint16_t y_length = (y2 - y1) * y_adder;
        if (x_length >= y_length) {
            double ratio = (double)(int)(y2 - y1) / (int)(x2 - x1);
            for (int16_t x = 0; x != x2 - x1; x += x_adder) {
                screen->cache(x1 + x, y1 + ratio * x, color);
            }
        } else {
            double ratio = (double)(int)(x2 - x1) / (int)(y2 - y1);
            for (int16_t y = 0; y != y2 - y1; y += y_adder) {
                screen->cache(x1 + ratio * y, y1 + y, color);
            }
        }
    }
    screen->display();
}

template <typename P, typename C>
inline void Graphics<P, C>::drawCircle(P x, P y, P radius, C color) {
    screen->cache(x, y - radius, color);
    screen->cache(x, y + radius, color);
    for (int i = 1; i < radius; i++) {
        double angle = PI / 2 * (radius - i) / radius;
        int j = radius * cos(angle);
        int k = radius * sin(angle);
        screen->cache(x + k, y + j, color);
        screen->cache(x + k, y - j, color);
        screen->cache(x - k, y - j, color);
        screen->cache(x - k, y + j, color);
    }
    screen->cache(x - radius, y, color);
    screen->cache(x + radius, y, color);
    screen->display();
}

template <typename P, typename C>
inline void Graphics<P, C>::drawRectangle(P x1, P y1, P x2, P y2, C color) {
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y1, x1, y2, color);
    drawLine(x1, y2, x2, y2, color);
    drawLine(x2, y1, x2, y2, color);
}

template <typename P, typename C>
inline void Graphics<P, C>::fillScreen(C color) {
    screen->cache(0, 0, screen->getWidth() - 1, screen->getHeight() - 1, color);
    screen->display();
}

#endif