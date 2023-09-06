#include "../airduino.h"

#ifndef AIRDUNIO_LIB_COLOR

#define AIRDUNIO_LIB_COLOR 1

template<typename T>
class Color {
    public:
        const T black = 0;
        const T white = -1;
};

#endif