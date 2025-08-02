#ifndef AIRDUNIO_LIB_RAINBOW_LED
#define AIRDUNIO_LIB_RAINBOW_LED 1

#include "../airduino.h"
#include "../devices/led.hpp"

class RainbowLed {
    LedRgb *led_rgb;

    uint8_t index = 6;

    uint32_t colors[6]{
        255 << 16 | 0 << 8 | 0,
        255 << 16 | 255 << 8 | 0,
        0 << 16 | 255 << 8 | 0,
        0 << 16 | 255 << 8 | 255,
        0 << 16 | 0 << 8 | 255,
        255 << 16 | 0 << 8 | 255};

    inline uint8_t getRed(uint32_t value) {
        return (value & 255 << 16) >> 16;
    }

    inline uint8_t getGreen(uint32_t value) {
        return (value & 255 << 8) >> 8;
    }

    inline uint8_t getBlue(uint32_t value) {
        return value & 255;
    }

public:
    void use(LedRgb *led_rgb) {
        this->led_rgb = led_rgb;
    }

    void changeToNextColor() {
        index = index < 6 ? (1 + index) % 6 : 0;

        led_rgb->light(getRed(colors[index]), getGreen(colors[index]), getBlue(colors[index]));
    }

    void changeGradually(uint8_t percent) {
        static int8_t adder_color_indexes[5]{2, -1, 3, -2, 1};

        if (percent > 99) {
            index = 5;
            led_rgb->light(getRed(colors[index]), getGreen(colors[index]), getBlue(colors[index]));
            return;
        }

        uint8_t index = percent / 20;
        uint8_t adder = percent % 20;
        int8_t adder_color_index = adder_color_indexes[index];
        uint32_t value = 0;
        uint8_t color_index = 0;

        if (adder_color_index < 0) {
            color_index = -adder_color_index - 1;
            value = colors[index] - ((adder * 13) << ((2 - color_index) * 8));
        } else {
            color_index = adder_color_index - 1;
            value = colors[index] + ((adder * 13) << ((2 - color_index) * 8));
        }

        led_rgb->light(getRed(value), getGreen(value), getBlue(value));
    }

    void turnOff() {
        index = 6;
        led_rgb->light(0, 0, 0);
    }

    uint8_t getLevel() {
        return index + 1;
    }
};

#endif