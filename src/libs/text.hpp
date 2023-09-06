#include "../airduino.h"
#include "display.hpp"

#ifndef AIRDUNIO_LIB_TEXT

#define AIRDUNIO_LIB_TEXT 1

#include "../thirds/bitsfont_6x8.h"

template<typename T>
class Text {
    public:
        Text(Display<T>& display);
        Text<T>& at(uint16_t x, uint16_t y);
        Text<T>& font(uint8_t width, uint8_t height);
        Text<T>& color(T color);
        Text<T>& print(char* content);
        void flush();
    private:
        Display<T>& display;
        uint16_t x = 0;
        uint16_t y = 0;
        uint8_t font_width = 6;
        uint8_t font_height = 8;
        uint16_t font_mask = 0x80;
        T font_color = -1;
};

template <typename T>
Text<T>::Text(Display<T> &display) : display(display) {
}

template <typename T>
Text<T> &Text<T>::at(uint16_t x, uint16_t y) {
    this->x = x;
    this->y = y;
    return *this;
}

template <typename T>
inline Text<T> &Text<T>::font(uint8_t width, uint8_t height) {
    this->font_width = width;
    this->font_height = height;
    this->font_mask = 0x80;
    return *this;
}

template <typename T>
Text<T> &Text<T>::color(T color) {
    font_color = color;
    return *this;
}

template <typename T>
Text<T> &Text<T>::print(char *content) {
    size_t length = strlen(content);
    for (uint16_t i = 0; i < length; i++) {
        uint16_t char_j = content[i] * font_height;
        for (int8_t j = 0; j < font_height; j++) {
            unsigned char char_row = pgm_read_byte(&BITFONT_6X8_ASCII[char_j + j]);
            for (uint8_t k = 0; k < font_width; k++) {
                if (char_row & font_mask) {
                    display.fillPoint(x + k, y + j, font_color);
                }
                char_row <<= 1;
            }
        }
        x += (font_width + 1);
    }
    return *this;
}

template <typename T>
void Text<T>::flush() {
}

#endif

