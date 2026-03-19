#ifndef AIRDUNIO_LIB_PRESSING
#define AIRDUNIO_LIB_PRESSING 1

#include "../airduino.h"
#include "../devices/button.hpp"

/**
 * current: (s p1) (s r1), next: (s p2) (s r2)
 * current is long: r1 - p1 > l, current is short: r1 - p1 <= l
 * next is new: long || (short && p2 - r1 > g), next is continue: short && p2 - r1 <= g
 * current is finish: now - r1 > g
 */

class Pressing {
private:
    Button *button;
    uint8_t counter = 0;

    uint32_t last_press_time = 0;
    uint32_t last_release_time = 0;

    uint16_t shake_duration = 10;

    uint16_t long_duration = 1000;

    uint16_t gap_duration = 300;

public:
    Pressing() {}

    Pressing(uint16_t long_duration, uint16_t gap_duration) : long_duration(long_duration), gap_duration(gap_duration) {
    }

    void use(Button *button) {
        use(button, [](bool press_state) {});
    }

    void use(Button *button, void (*interrupt_function)(bool press_state)) {
        this->button = button;
        auto wrapper_interrupt_function = [&]() {
            count();
            interrupt_function(button->isPress());
        };
        attachInterrupt(digitalPinToInterrupt(button->getPin()), wrapper_interrupt_function, CHANGE);
    }

    void count() {
        uint32_t now = millis();
        bool press_state = button->isPress();

        // delay(shake_duration);
        if (button->isPress() != press_state) return;

        if (press_state) {
            // if (now - last_press_time <= shake_duration) return;
            if (last_release_time - last_press_time > long_duration || now - last_release_time > gap_duration) {
                counter = 0;
            }
            last_press_time = now;
        } else {
            // if (now - last_release_time <= shake_duration) return;
            if (counter != 0 || now - last_press_time <= long_duration) {
                ++counter;
            }
            last_release_time = now;
        }
    }

    bool isFinish() {
        return !button->isPress() && millis() - last_release_time >= gap_duration;
    }

    uint16_t getDuration() {
        if (button->isPress()) {
            return millis() - last_press_time;
        }
        return 0;
    }

    uint8_t getCountAndClear() {
        uint8_t result = counter;
        counter = 0;
        return result;
    }
};

#endif