#include "../airduino.h"

#ifndef AIRDUNIO_LIB_COORDINATE

#define AIRDUNIO_LIB_COORDINATE 1

template<typename T> 
class Coordinate {
    public:
        Coordinate(uint16_t width, uint16_t height);
        ~Coordinate();
        virtual void mark(uint16_t x, uint16_t y, T color);
        virtual T getMark(uint16_t x, uint16_t y);
    protected:
        uint16_t width;
        uint16_t height;
        T *points;
};

template<typename T>
inline void Coordinate<T>::mark(uint16_t x, uint16_t y, T color) {
    points[width * y + x] = color;
}

template<typename T>
inline T Coordinate<T>::getMark(uint16_t x, uint16_t y) {
    return points[width * y + x];
}

template<typename T>
Coordinate<T>::Coordinate(uint16_t width, uint16_t height) : width(width), height(height) {
    points = new T[width * height];
}

template<typename T>
Coordinate<T>::~Coordinate() {
    delete[] points;
}

#endif