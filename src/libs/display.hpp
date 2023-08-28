#include "../airduino.h"

#ifndef AIRDUNIO_LIB_DISPLAY

#define AIRDUNIO_LIB_DISPLAY 1

class Display {
    public:
        virtual void refresh() = 0;
        virtual void fillPoint(uint16_t x, uint16_t y, uint16_t color) = 0;
        virtual void fillBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) = 0;
};

#endif