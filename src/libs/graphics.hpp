#include "../airduino.h"
#include "coordinate.hpp"
#include "display.hpp"

#ifndef AIRDUNIO_LIB_GRAPHICS

#define AIRDUNIO_LIB_GRAPHICS 1

class Graphics {
    public:
        Graphics(Display& display, uint16_t width, uint16_t height);
        Graphics& drawPoint(uint16_t x, uint16_t y, uint16_t color);
        Graphics& drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
        Graphics& fillScreen(uint16_t color);
        void flush();
    private:
        uint16_t width;
        uint16_t height;
        Display& display;
        // bool *rowMark;
};

#endif