#include "../airduino.h"

#ifndef AIRDUNIO_LIB_COORDINATE

#define AIRDUNIO_LIB_COORDINATE 1

class Coordinate {
    public:
        Coordinate(uint16_t width, uint16_t height);
        ~Coordinate();
    protected:
        virtual void mark(uint16_t x, uint16_t y, uint16_t color);
        virtual uint16_t getMark(uint16_t x, uint16_t y);
        uint16_t width;
        uint16_t height;
        uint16_t *points;
};

#endif