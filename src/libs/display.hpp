#include "../airduino.h"

#ifndef AIRDUNIO_LIB_DISPLAY

#define AIRDUNIO_LIB_DISPLAY 1

template<typename T>
class Display {
    public:
        Display(uint16_t width, uint16_t height);
        virtual void refresh() = 0;
        virtual void fillPoint(uint16_t x, uint16_t y, T color) = 0;
        virtual void fillBlock(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, T color) = 0;
        uint16_t getWidth();
        uint16_t getHeight();
    protected:
        uint16_t width;
        uint16_t height;
};

template<typename T>
Display<T>::Display(uint16_t width, uint16_t height) : width(width), height(height) {
}

template<typename T>
inline uint16_t Display<T>::getWidth() {
    return width;
}

template<typename T>
inline uint16_t Display<T>::getHeight() {
    return height;
}

#endif