#ifndef AIRDUNIO_DEVICE_LED
#define AIRDUNIO_DEVICE_LED 1

#include "../airduino.h"

class LedRgb {
    uint8_t red_pin, green_pin, blue_pin;
    uint8_t current_red_value, current_green_value, current_blue_value;

public:
    LedRgb() = delete;

    LedRgb(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin) : red_pin(red_pin), green_pin(green_pin), blue_pin(blue_pin) {}

    void initialize() {
        pinMode(red_pin, OUTPUT);
        pinMode(green_pin, OUTPUT);
        pinMode(blue_pin, OUTPUT);
    }

    void light(uint8_t pin, uint8_t value) {
        analogWrite(pin, value);
        if (pin == red_pin) current_red_value = value;
        if (pin == green_pin) current_green_value = value;
        if (pin == blue_pin) current_blue_value = value;
    }

    void light(uint8_t red_value, uint8_t green_value, uint8_t blue_value) {
        analogWrite(red_pin, red_value);
        analogWrite(green_pin, green_value);
        analogWrite(blue_pin, blue_value);
        current_red_value = red_value;
        current_green_value = green_value;
        current_blue_value = blue_value;
    }

    void getBrightness(uint8_t pin, uint8_t *value) {
        *value = pin == red_pin ? current_red_value : (pin == green_pin ? current_green_value : current_blue_value);
    }

    void getBrightness(uint8_t *red_value, uint8_t *green_value, uint8_t *blue_value) {
        *red_value = current_red_value;
        *green_value = current_green_value;
        *blue_value = current_blue_value;
    }

    uint8_t getRedPin() {
        return red_pin;
    }

    uint8_t getGreenPin() {
        return green_pin;
    }

    uint8_t getBluePin() {
        return blue_pin;
    }
};

#endif