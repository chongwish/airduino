#ifndef AIRDUNIO_APP_TEXT
#define AIRDUNIO_APP_TEXT 1

#include "../airduino.h"
#include "../devices/screen.hpp"
#include "../thirds/bitsfont_6x8.h"

template <typename P, typename C>
class Text {
    ScreenDisplay<P, C> *screen;
    P x = 0;
    P y = 0;
    P font_width = 6;
    P font_height = 8;
    P font_mask = 0x80;
    C font_color = -1;

public:
    void use(ScreenDisplay<P, C> *screen);
    Text<P, C> &at(P x, P y);
    Text<P, C> &font(P width, P height);
    Text<P, C> &color(C color);
    Text<P, C> &print(char *content);
    void flush();
};

template <typename P, typename C>
void Text<P, C>::use(ScreenDisplay<P, C> *screen) {
    this->screen = screen;
}

template <typename P, typename C>
Text<P, C> &Text<P, C>::at(P x, P y) {
    screen->display();
    this->x = x;
    this->y = y;
    return *this;
}

template <typename P, typename C>
Text<P, C> &Text<P, C>::font(P width, P height) {
    this->font_width = width;
    this->font_height = height;
    return *this;
}

template <typename P, typename C>
Text<P, C> &Text<P, C>::color(C color) {
    font_color = color;
    return *this;
}

template <typename P, typename C>
Text<P, C> &Text<P, C>::print(char *content) {
    size_t length = strlen(content);
    for (uint16_t i = 0; i < length; i++) {
        uint16_t char_j = content[i] * font_height;
        for (int8_t j = 0; j < font_height; j++) {
            unsigned char char_row = pgm_read_byte(&BITFONT_6X8_ASCII[char_j + j]);
            for (uint8_t k = 0; k < font_width; k++) {
                if (char_row & font_mask) {
                    screen->cache(x + k, y + j, font_color);
                }
                char_row <<= 1;
            }
        }
        x += (font_width + 1);
    }
    return *this;
}

template <typename P, typename C>
void Text<P, C>::flush() {
    screen->display();
}

#endif