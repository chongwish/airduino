#ifndef AIRDUNIO_LIB_PRESSING
#define AIRDUNIO_LIB_PRESSING 1

#include "../airduino.h"
#include "../devices/button.hpp"

class Pressing {
private:
    Button *button;
    uint8_t counter = 0;

    uint32_t first_time = 0;
    uint32_t last_time = 0;

    uint16_t max_blank_time = 400;

public:
    void use(Button *button, int interrupt_method, void (*interrupt_function)()) {
        this->button = button;
        attachInterrupt(digitalPinToInterrupt(button->getPin()), interrupt_function, interrupt_method);
    }

    void count() {
        uint32_t now = millis();

        if (first_time == 0 || last_time == 0 || now - last_time >= max_blank_time) {
            first_time = now;
            counter = 1;
        } else {
            ++counter;
        }

        last_time = now;
    }

    bool isFinish() {
        if (button->isPress()) {
            last_time = millis();
            return false;
        }

        return millis() - last_time >= max_blank_time;
    }

    void clear() {
        counter = 0;
        first_time = 0;
        last_time = 0;
    }

    uint16_t getDuration() {
        isFinish();
        return last_time - first_time;
    }

    uint8_t getCount() {
        isFinish();
        return counter;
    }
};

#endif