#ifndef AIRDUNIO_LIB_COORDINATE
#define AIRDUNIO_LIB_COORDINATE 1

#include "../airduino.h"

template <typename T = uint8_t, typename P = uint8_t>
class Coordinate {
    P width;
    P height;
    T *points;

public:
    Coordinate() = delete;
    Coordinate(const P &width, const P &height) : width(width), height(height) {
        points = new T[width * height]{};
    }
    ~Coordinate() {
        delete[] points;
    }
    inline void mark(const P &x, const P &y, const T &value) {
        points[width * y + x] = value;
    }
    inline T getMark(const P &x, const P &y) {
        return points[width * y + x];
    }
};

#endif