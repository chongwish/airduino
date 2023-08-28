#include "coordinate.hpp"

inline void Coordinate::mark(uint16_t x, uint16_t y, uint16_t color) {
    points[height * y + x] = color;
}

inline uint16_t Coordinate::getMark(uint16_t x, uint16_t y) {
    return points[height * y + x];
}

Coordinate::Coordinate(uint16_t width, uint16_t height) : width(width), height(height) {
    points = new uint16_t[width * height];
}

Coordinate::~Coordinate() {
    delete[] points;
}